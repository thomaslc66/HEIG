# Issues List

<!-- STORY -->

### Issue List

Then if you want a list of issues a the bottom just add a IssueList tag

```js
<IssuesList tab={['1', '2', '3']} />
```

tab is an array you can pass from the layout you call an `<IssuesList />`

```js
tab={["1", "2", "3"]}
```

Exemple: (From render method of a layout class)

```js
state = {
    tab: ["ma valeur 1", "2", "Mon Titre"]
}

</div>
    <IssuesLayout tab={this.state.tab} />
</div>
```

You list will be composed of 3 `<IssueLine>` elements with the title set to the
text in the tab array
