## CLD LABO 06
Thomas Léchaire && Michael Brouchoud


##### Return to the output of running the web.yml playbook the first time. There is one additional task that was not in the playbook. Which one? Among the tasks that are in the playbook there is one task that Ansible marked as ok. Which one? Do you have a possible explanation?

When we start the web.yml deployement config, the first task that is not listed in our command list is the [Gathering Facts] task. This Ansible Task is "a module automatically called by playbooks to gather useful variables about the remote hosts that can be user in playbooks" (From Ansible Doc). 

The enable configuration task is marked as ok. This task use the module file and the parameter state=link. In the Ansible Doc we can find this in the file (state) module: "If link, the symbolic link will be created or changed." As it's the first time the link is not changed but created so the return value is ok. If the src= or des= are changed, maybe the state will passed from ok to changed.


##### Re-run the web.yml playbook a second time. In principle nothing should have changed. Compare Ansible's output with the first run. Which tasks are marked as changed?

Only the restat nginx task is marked changed. The other 6 tasks including the Gathering Facts are ok.


##### SSH into the managed server. Modify the nginx configuration file /etc/nginx/sites-available/default, for example by adding a line with a comment. Re-run the playbook. What does Ansible do to the file and what does it show in its output?

The commented line is erased because the file is replaced by the playbooks. We can see it beacause the task in the playbook is not "ok" anymore but the status is "changed".

##### Do something more drastic like completely removing the homepage and repeat the previous question.

When the file is deleted, the nginx server return a 403 error page. Then as we might expected, the file is pushed back again on the server when we run the playbokk again. We can also see it because the status of the play [copy index.html] is now equal to "changed" 


##### Modifications of the web.yml with handlers

```
- name: Configure webserver with nginx
  hosts: webservers
  sudo: True
  handlers:
    - name: restart nginx
      service: name=nginx state=restarted
      listen: "restart"
  tasks:
    - name: install nginx
      apt: name=nginx update_cache=yes
      notify: "restart"
    - name: copy nginx config file
      copy: src=files/nginx.conf dest=/etc/nginx/sites-available/default
      notify: "restart"
    - name: enable configuration
      file: >
        dest=/etc/nginx/sites-enabled/default
        src=/etc/nginx/sites-available/default
        state=link
      notify: "restart"
    - name: copy index.html
      template: src=templates/index.html.j2 dest=/usr/share/nginx/html/index.html mode=0644
      notify: "restart"
```


##### In this task you will add more managed servers that will be configured by the same playbook.


##### Re-run the web.yml playbook. What do you observe in Ansible's output?

Each play (task) has now two status, one for each server. You can now see which server is changed or not and at then end you have a recap for each server, plus with the handlers, only the server 2 was restarted as when didn't made any changes to the server 1.

##### Test the new server by pointing your web browser to it.

The same page is displayed, the deployement seems to work.

##### What happens if a server is not reachable? Shut down the second instance and re-run the playbook.

When the first task added by ansible [Gathering Facts] return a fatal error => UNREACHABLE, then all the subsequent tasks are only made to the living instances, so only the server one received the tasks. At the end we have a RECAP of the PLAY and we see the server 1 with 5 ok, and the server 2 with unreachable=1. He also create a web.retry file with the name of the file server that Ansible wasn't able to reach and apply the playbook play (tasks)

##### Suppose you now have 10 web servers in production that you have configured using Ansible. You are working in the IT department of a company and some of your system administrator colleagues who don't use Ansible have logged manually into some of the servers to fix certain things. You don't know what they did exactly. What do you need to do to bring all 10 servers again to the initial state? We'll exclude drastic changes by your colleagues for this question.

As we have seen in the previous tests, when we delete of modify some files in the webservers, Ansible detect the change and replace the file with the file from the playbook. Then he tells us for which servers the change was made and the file was replaced. So if some of my coworkers have made manual changes, running the playbook again will then erase those changes, but maybe thoses changes are important, so i maybe need to ask them what they have done and integrate those changes directly in the ansible config or the ngninx config to redeploy to all our servers.
