# Issues Line

<!-- STORY -->

#### Line

each line is automaticaly generated from the tab given to a `<IssuesList />`
component. But you can pass them some parameters

```
<IssuesLine
    status='open' || 'close'
    title="My super text"
    subTitle="Sous-titre de l'issue"
    id={the number of the line}
    key={must be a unique identifier for each line otherwise it will crash (a number is totaly fine)}
/>
```
