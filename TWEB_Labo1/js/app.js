var follow = false;
var posts = 4219;
var follows = 3200;
var comments = 6500000;


window.onload = function() {
    displayNumbers();
  };


function displayNumbers(){
    document.getElementById("posts_nbr").innerText = displayConverter(posts);
    document.getElementById("follows_nbr").innerText = displayConverter(follows);
    document.getElementById("comments_nbr").innerText = displayConverter(comments);
}



document.getElementById("follow_button").onclick = function (){
    var object = document.getElementById("follows_nbr");
    var button = document.getElementById("follow_button");
    
    if(!follow){
        button.innerText = "Unfollow";
        button.style.background='#FF0000'
        follows = (follows+1);
        console.log(follows);
        follow = true;
    }else{
        button.innerText = "Follow";
        button.style.background='#67C15E'
        follows = (follows-1);
        console.log(follows);
        follow = false;
    }
    
    object.innerText = "" + displayConverter(follows);
}


function formData(num){
    return new Intl.NumberFormat().format(Math.round(num*10)/10);
}


function displayConverter(number){
    if(number >= 1000000)
        return formData(number/1000000)+'M';
    if(number >= 1000)
        return formData(number/1000)+'k';
    return formData(number);
}