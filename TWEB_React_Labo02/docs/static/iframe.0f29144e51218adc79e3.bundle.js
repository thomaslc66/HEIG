(window.webpackJsonp=window.webpackJsonp||[]).push([[0],{129:function(e,t,n){"use strict";var s=n(5),r=n.n(s),a=n(6),o=n.n(a),i=n(7),c=n.n(i),l=n(8),u=n.n(l),m=n(9),d=n.n(m),p=n(3),h=n.n(p),f=n(4),y=n.n(f),E=n(0),g=n.n(E),v=n(31),S=n(45),O=function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{}),n}return d()(t,e),o()(t,[{key:"render",value:function(){return g.a.createElement("form",{className:"form-inline"},g.a.createElement(v.a,{value:"light",text:g.a.createElement(S.a,null)}),g.a.createElement("input",{className:"form-control mr-sm-2",type:"search",placeholder:"is:issue is:open"}),g.a.createElement("button",{className:"btn btn-outline-succes my-sm-0",type:"submit"},"Search"))}}]),t}(E.Component);t.a=O,O.__docgenInfo={description:"",methods:[],displayName:"SearchBar"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\components\\bar\\searchBar.jsx"]={name:"SearchBar",docgenInfo:O.__docgenInfo,path:"src\\components\\bar\\searchBar.jsx"})},130:function(e,t,n){"use strict";var s=n(5),r=n.n(s),a=n(6),o=n.n(a),i=n(7),c=n.n(i),l=n(8),u=n.n(l),m=n(9),d=n.n(m),p=n(3),h=n.n(p),f=n(4),y=n.n(f),E=n(0),g=n.n(E),v=n(30),S=function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{text:n.props.text,value:n.props.value}),y()(h()(h()(n)),"styles",{fontWeight:n.props.fontWeight}),n}return d()(t,e),o()(t,[{key:"render",value:function(){return g.a.createElement("button",{style:this.styles,type:"button",className:this.renderClasses(),onClick:this.props.onClick},g.a.createElement(v.a,{name:this.props.iconName,color:this.props.iconColor,right:10}),this.props.text)}},{key:"renderClasses",value:function(){return"btn btn-"+this.state.value}}]),t}(E.Component);t.a=S,S.__docgenInfo={description:"",methods:[{name:"renderClasses",docblock:null,modifiers:[],params:[],returns:null}],displayName:"Button"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\components\\buttons\\buttonWithIcon.jsx"]={name:"Button",docgenInfo:S.__docgenInfo,path:"src\\components\\buttons\\buttonWithIcon.jsx"})},186:function(e,t,n){"use strict";var s=n(5),r=n.n(s),a=n(6),o=n.n(a),i=n(7),c=n.n(i),l=n(8),u=n.n(l),m=n(9),d=n.n(m),p=n(3),h=n.n(p),f=n(4),y=n.n(f),E=n(0),g=n.n(E),v=n(30),S=n(45),O=function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{open:n.props.openNbr||0,close:n.props.closeNbr||0,margin:25}),y()(h()(h()(n)),"styles",{display:"flex",justifyContent:"space-between"}),y()(h()(h()(n)),"divStyleOpen",{marginLeft:10,fontWeight:"bold"}),y()(h()(h()(n)),"divStyle",{marginLeft:15}),n}return d()(t,e),o()(t,[{key:"render",value:function(){return g.a.createElement("li",{style:this.styles,className:"list-group-item list-group-item-secondary"},g.a.createElement("div",{style:this.styles},g.a.createElement(v.a,{name:"open"}),g.a.createElement("div",{style:this.divStyleOpen},this.props.openNbr||0," Open"),g.a.createElement("div",{style:this.divStyle},g.a.createElement(v.a,{name:"close",color:"red"})," ",this.state.close," Closed")),g.a.createElement("div",{style:this.styles},g.a.createElement(S.a,{name:"Author"}),g.a.createElement(S.a,{name:"Labels"}),g.a.createElement(S.a,{name:"Projects"}),g.a.createElement(S.a,{name:"Milestones"}),g.a.createElement(S.a,{name:"Assignee"}),g.a.createElement(S.a,{name:"Sort"})))}}]),t}(E.Component);t.a=O,O.__docgenInfo={description:"",methods:[],displayName:"IssuesResume"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\components\\issues\\issuesResume.jsx"]={name:"IssuesResume",docgenInfo:O.__docgenInfo,path:"src\\components\\issues\\issuesResume.jsx"})},187:function(e,t,n){"use strict";var s=n(5),r=n.n(s),a=n(6),o=n.n(a),i=n(7),c=n.n(i),l=n(8),u=n.n(l),m=n(9),d=n.n(m),p=n(3),h=n.n(p),f=n(4),y=n.n(f),E=n(0),g=n.n(E),v=n(208),S=function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{tabs:n.props.tab}),n}return d()(t,e),o()(t,[{key:"renderIssueId",value:function(e){return"Super titre de mon problème avec numérotation de l'issue N°"+e}},{key:"render",value:function(){var e=this;return g.a.createElement("ul",{className:"list-group"},this.state.tabs.map(function(t){return g.a.createElement(v.a,{status:"open",title:e.renderIssueId(t),subTitle:"Sous-titre de l'issue",id:t,key:t})}))}}]),t}(E.Component);t.a=S,S.__docgenInfo={description:"",methods:[{name:"renderIssueId",docblock:null,modifiers:[],params:[{name:"id",type:null}],returns:null}],displayName:"IssuesList"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\components\\issues\\issuesList.jsx"]={name:"IssuesList",docgenInfo:S.__docgenInfo,path:"src\\components\\issues\\issuesList.jsx"})},207:function(e,t,n){"use strict";var s=n(5),r=n.n(s),a=n(6),o=n.n(a),i=n(7),c=n.n(i),l=n(8),u=n.n(l),m=n(9),d=n.n(m),p=n(3),h=n.n(p),f=n(4),y=n.n(f),E=n(0),g=n.n(E),v=n(129),S=n(30),O=function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{title:"Github"}),n}return d()(t,e),o()(t,[{key:"render",value:function(){return g.a.createElement("nav",{className:"navbar navbar-expand-lg navbar-dark bg-dark"},g.a.createElement("div",{className:"container"},g.a.createElement("div",null,g.a.createElement(S.a,{size:"medium",color:"white"}),g.a.createElement("a",{className:"navbar-brand",href:"/",style:{marginLeft:10}},this.state.title)),g.a.createElement(v.a,null)))}}]),t}(E.Component);t.a=O,O.__docgenInfo={description:"",methods:[],displayName:"Header"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\containers\\header.jsx"]={name:"Header",docgenInfo:O.__docgenInfo,path:"src\\containers\\header.jsx"})},208:function(e,t,n){"use strict";var s=n(5),r=n.n(s),a=n(6),o=n.n(a),i=n(7),c=n.n(i),l=n(8),u=n.n(l),m=n(9),d=n.n(m),p=n(3),h=n.n(p),f=n(4),y=n.n(f),E=n(0),g=n.n(E),v=n(30),S=function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{title:n.props.title||"Titre par default",subTitle:n.props.subTitle||"Sous-titre par default"}),y()(h()(h()(n)),"stylesRow",{textAlign:"left",display:"flex",flexDirection:"row",justifyContent:"left"}),y()(h()(h()(n)),"styleColumns",{marginLeft:15}),n}return d()(t,e),o()(t,[{key:"render",value:function(){return g.a.createElement("li",{className:"list-group-item list-group-item-action"},g.a.createElement("div",{style:this.stylesRow},g.a.createElement(v.a,{name:this.props.status}),g.a.createElement("div",{style:this.styleColumns,classname:"container"},g.a.createElement("div",{classname:"row"},g.a.createElement("h4",null,this.state.title," ")),g.a.createElement("div",{classname:"row"},g.a.createElement("h8",null,this.state.subTitle)))))}}]),t}(E.Component);t.a=S,S.__docgenInfo={description:"",methods:[],displayName:"IssuesLine"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\components\\issues\\issuesLine.jsx"]={name:"IssuesLine",docgenInfo:S.__docgenInfo,path:"src\\components\\issues\\issuesLine.jsx"})},209:function(e,t,n){"use strict";var s=n(5),r=n.n(s),a=n(6),o=n.n(a),i=n(7),c=n.n(i),l=n(8),u=n.n(l),m=n(9),d=n.n(m),p=n(3),h=n.n(p),f=n(4),y=n.n(f),E=n(0),g=n.n(E),v=n(130),S=function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{time:n.props.time||0}),n}return d()(t,e),o()(t,[{key:"iconButton",value:function(){return"close"===this.props.status?g.a.createElement(v.a,{iconName:"close",text:"Closed",value:"danger",iconColor:"white"}):g.a.createElement(v.a,{iconName:"open",text:"Open",value:"success",iconColor:"white"})}},{key:"render",value:function(){return g.a.createElement("div",{style:{display:"flex",marginBottom:30,alignItems:"center"}},this.iconButton(),g.a.createElement("h6",{style:{marginLeft:30,color:"gray"}},"Kim-Jung 1 opened this issue ",this.state.time,"h ago"))}}]),t}(E.Component);t.a=S,S.__docgenInfo={description:"",methods:[{name:"iconButton",docblock:null,modifiers:[],params:[],returns:null}],displayName:"IssuesStatus"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\components\\issues\\issuesStatus.jsx"]={name:"IssuesStatus",docgenInfo:S.__docgenInfo,path:"src\\components\\issues\\issuesStatus.jsx"})},210:function(e,t,n){"use strict";var s=n(5),r=n.n(s),a=n(6),o=n.n(a),i=n(7),c=n.n(i),l=n(8),u=n.n(l),m=n(9),d=n.n(m),p=n(3),h=n.n(p),f=n(4),y=n.n(f),E=n(0),g=n.n(E),v=function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{}),y()(h()(h()(n)),"styles",{verticalAlign:"middle",height:70,weight:70}),n}return d()(t,e),o()(t,[{key:"render",value:function(){return g.a.createElement("img",{style:this.styles,alt:"avatar",src:this.props.src})}}]),t}(E.Component);t.a=v,v.__docgenInfo={description:"",methods:[],displayName:"Gravatar"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\components\\glyphicon\\gravatar.jsx"]={name:"Gravatar",docgenInfo:v.__docgenInfo,path:"src\\components\\glyphicon\\gravatar.jsx"})},211:function(e,t,n){"use strict";var s=n(5),r=n.n(s),a=n(6),o=n.n(a),i=n(7),c=n.n(i),l=n(8),u=n.n(l),m=n(9),d=n.n(m),p=n(3),h=n.n(p),f=n(4),y=n.n(f),E=n(0),g=n.n(E),v=(n(30),n(45),function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{open:n.props.index,close:n.props.closeNbr||0,margin:25}),y()(h()(h()(n)),"styles",{display:"flex",justifyContent:"space-between"}),y()(h()(h()(n)),"divStyleOpen",{marginLeft:15,fontWeight:"bold"}),y()(h()(h()(n)),"divStyle",{marginLeft:15}),n}return d()(t,e),o()(t,[{key:"render",value:function(){return g.a.createElement("li",{style:this.styles,className:"list-group-item list-group-item-secondary"},g.a.createElement("div",{style:this.styles},this.props.username," commented 11 hours ago"),g.a.createElement("div",{style:this.styles},"..."))}}]),t}(E.Component));t.a=v,v.__docgenInfo={description:"",methods:[],displayName:"IssuesHeader"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\components\\issues\\issuesHeader.jsx"]={name:"IssuesHeader",docgenInfo:v.__docgenInfo,path:"src\\components\\issues\\issuesHeader.jsx"})},212:function(e,t,n){"use strict";var s=n(5),r=n.n(s),a=n(6),o=n.n(a),i=n(7),c=n.n(i),l=n(8),u=n.n(l),m=n(9),d=n.n(m),p=n(3),h=n.n(p),f=n(4),y=n.n(f),E=n(0),g=n.n(E),v=n(31),S=function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{}),n}return d()(t,e),o()(t,[{key:"render",value:function(){return g.a.createElement("div",{style:{display:"flex",textAlign:"left"}},g.a.createElement("h1",null,this.props.text),g.a.createElement("div",{className:"ml-auto p-2"},g.a.createElement(v.a,{value:"success",text:"New Issue"})))}}]),t}(E.Component);t.a=S,S.__docgenInfo={description:"",methods:[],displayName:"IssuesTitle"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\components\\issues\\issuesTitle.jsx"]={name:"IssuesTitle",docgenInfo:S.__docgenInfo,path:"src\\components\\issues\\issuesTitle.jsx"})},214:function(e,t,n){"use strict";var s=n(5),r=n.n(s),a=n(6),o=n.n(a),i=n(7),c=n.n(i),l=n(8),u=n.n(l),m=n(9),d=n.n(m),p=n(3),h=n.n(p),f=n(4),y=n.n(f),E=n(0),g=n.n(E),v=n(210),S=n(211),O=function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{}),n}return d()(t,e),o()(t,[{key:"render",value:function(){return g.a.createElement("ul",{className:"list-group"},g.a.createElement("li",{className:"list-group-item"},g.a.createElement("div",{style:{textAlign:"left"}},this.props.text,"Hello every body, I'm currently dealing with a painfull situation.",g.a.createElement("br",null),"I've been playing with some of my fireworks in my garden, because i really like big fireworks. It's not always intentional but you know sometime fireworks are not really precise when we throw them. And i don't know why but a lot of other countries are afraid. I'm only having fun with some of my friends. The Us president Trumpy Trump always call me to stop my game and tell me i'm childish and that i need to grow up. Even the French President Maccaron call me sometimes.",g.a.createElement("br",null),g.a.createElement("br",null),"I don't know what's bother them so much, i don't tell them anything an 4 or 14 july. What's the big deal if i'm playing ?? Ok sometimes some of my fireworks are nuclear but it's because i have a lot of them so sometimes i can mix them up.",g.a.createElement("br",null),g.a.createElement("br",null),"Can you help me finding a solution to make them understand my point of view?")))}}]),t}(E.Component),x=O;O.__docgenInfo={description:"",methods:[],displayName:"IssuesDetails"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\components\\issues\\issuesDetails.jsx"]={name:"IssuesDetails",docgenInfo:O.__docgenInfo,path:"src\\components\\issues\\issuesDetails.jsx"});var b=function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{}),n}return d()(t,e),o()(t,[{key:"render",value:function(){return g.a.createElement("div",{className:"col"},g.a.createElement("div",{className:"row"},g.a.createElement("div",{style:{marginRight:20},className:"col-lg-1 col-md-1"},g.a.createElement(v.a,{src:"/img/avatar.png"})),g.a.createElement("div",{className:"col col-md col-sm"},g.a.createElement(S.a,{username:this.props.username}),g.a.createElement(x,{text:this.props.text}))))}}]),t}(E.Component);t.a=b;b.__docgenInfo={description:"",methods:[],displayName:"IssuesComments"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\components\\issues\\issuesComments.jsx"]={name:"IssuesComments",docgenInfo:b.__docgenInfo,path:"src\\components\\issues\\issuesComments.jsx"})},30:function(e,t,n){"use strict";var s=n(5),r=n.n(s),a=n(6),o=n.n(a),i=n(7),c=n.n(i),l=n(8),u=n.n(l),m=n(9),d=n.n(m),p=n(3),h=n.n(p),f=n(4),y=n.n(f),E=n(0),g=n.n(E),v=n(131),S=function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{green:"#28a745",open:v.b,close:v.a,filter:v.d,github:v.c}),y()(h()(h()(n)),"styles",{color:n.props.color||n.state.green,marginRight:n.props.right||0,marginLeft:n.props.left||0}),n}return d()(t,e),o()(t,[{key:"selectIcon",value:function(){var e;switch(this.props.name){case"open":e=this.state.open;break;case"close":e=this.state.close;break;case"filter":e=this.state.filter;break;default:e=this.state.github}return e}},{key:"render",value:function(){return g.a.createElement("span",{style:this.styles},g.a.createElement(v.e,{icon:this.selectIcon(),verticalAlign:"middle",size:this.props.size}))}}]),t}(E.Component);t.a=S,S.__docgenInfo={description:"",methods:[{name:"selectIcon",docblock:null,modifiers:[],params:[],returns:null}],displayName:"Icon"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\components\\glyphicon\\icon.jsx"]={name:"Icon",docgenInfo:S.__docgenInfo,path:"src\\components\\glyphicon\\icon.jsx"})},31:function(e,t,n){"use strict";var s=n(5),r=n.n(s),a=n(6),o=n.n(a),i=n(7),c=n.n(i),l=n(8),u=n.n(l),m=n(9),d=n.n(m),p=n(3),h=n.n(p),f=n(4),y=n.n(f),E=n(0),g=n.n(E),v=(n(30),function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{text:n.props.text,value:n.props.value}),y()(h()(h()(n)),"styles",{fontWeight:n.props.fontWeight}),n}return d()(t,e),o()(t,[{key:"render",value:function(){return g.a.createElement("button",{style:this.styles,type:"button",className:this.renderClasses(),onClick:this.props.onClick},this.props.text)}},{key:"renderClasses",value:function(){return"btn btn-"+this.state.value}}]),t}(E.Component));t.a=v,v.__docgenInfo={description:"",methods:[{name:"renderClasses",docblock:null,modifiers:[],params:[],returns:null}],displayName:"Button"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\components\\buttons\\button.jsx"]={name:"Button",docgenInfo:v.__docgenInfo,path:"src\\components\\buttons\\button.jsx"})},45:function(e,t,n){"use strict";var s=n(5),r=n.n(s),a=n(6),o=n.n(a),i=n(7),c=n.n(i),l=n(8),u=n.n(l),m=n(9),d=n.n(m),p=n(3),h=n.n(p),f=n(4),y=n.n(f),E=n(0),g=n.n(E),v=n(30),S=function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{}),y()(h()(h()(n)),"styles",{marginLeft:n.props.margin||15}),n}return d()(t,e),o()(t,[{key:"render",value:function(){return g.a.createElement("div",{style:this.styles},this.props.name||"Filters",g.a.createElement(v.a,{name:"filter",color:"gray",left:5}))}}]),t}(E.Component);t.a=S,S.__docgenInfo={description:"",methods:[],displayName:"Filter"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\components\\Filters\\filter.jsx"]={name:"Filter",docgenInfo:S.__docgenInfo,path:"src\\components\\Filters\\filter.jsx"})},536:function(e,t){e.exports='# Issues list layout\r\n\r\n\x3c!-- STORY --\x3e\r\n\r\nThis is the layout representing the issue\'s list. You can test it using the "New\r\nissue" Button.\r\n'},537:function(e,t){e.exports="# Issues detailed layout\r\n\r\n\x3c!-- STORY --\x3e\r\n\r\nThis is the layout representing the issue's details when you open it.\r\n"},538:function(e,t){e.exports='# BUTTTON\r\n\r\n\x3c!-- STORY --\x3e\r\n\r\n#### Buttons\r\n\r\nHere are all the Buttons color possibilities.\r\n\r\n```js\r\n<Button onClick={\x3c!-- function --\x3e} text="My Text" value="success" />\r\n<Button onClick={\x3c!-- function --\x3e} text="Button" value="info" />\r\n<Button onClick={\x3c!-- function --\x3e} text="Button" value="warning" />\r\n<Button onClick={\x3c!-- function --\x3e} text="Button" value="primary" />\r\n<Button onClick={\x3c!-- function --\x3e} text="Button" value="dark" />\r\n<Button onClick={\x3c!-- function --\x3e} text="Button" value="light" />\r\n<Button onClick={\x3c!-- function --\x3e} text="Button" value="secondary" />\r\n<Button onClick={\x3c!-- function --\x3e} text="My Text" value="danger" />\r\n```\r\n\r\nThe Button component can recieved multiple parameters:\r\n\r\n```\r\nonClick: a function from the parent\r\ntext: "The text of the button"\r\nvalue: {success, info, warning, primary, dark, light, secondary}\r\n```\r\n\r\nFor Button with Icon check how to do it on the Button sub-menu `with Icon`\r\n'},539:function(e,t){e.exports="# BUTTTON WITH ICON\r\n\r\n\x3c!-- STORY --\x3e\r\n\r\n#### Buttons\r\n\r\nHere are all the Buttons color possibilities.\r\n\r\n```js\r\n<ButtonWithIcon\r\n  text='Button'\r\n  value='success'\r\n  iconName='open'\r\n  iconColor='white'\r\n/>\r\n\r\n<ButtonWithIcon\r\n  text='Close'\r\n  value='danger'\r\n  iconName='close'\r\n  iconColor='white'\r\n/>\r\n```\r\n\r\nYou can pass to the button with icon multiple parameters\r\n\r\n```\r\ntext= 'My text that will appear in the button'\r\nvalue='success' 'primary' => see Button for all possible values\r\niconName= see Icon to see the possibilites you can pass to the iconName parameter\r\niconColor= standard css color\r\nfontWeight='bold','italic' etc...\r\n```\r\n"},540:function(e,t){e.exports='# ISSUES\r\n\r\n\x3c!-- STORY --\x3e\r\n\r\n### Issue\r\n\r\nThe code the get the following output:\r\n\r\n```js\r\n<IssuesResume />\r\n<IssuesList tab={["1", "2", "3"]} />\r\n```\r\n\r\n#### More Info\r\n\r\nTo have more info look at each compenents individualy\r\n'},541:function(e,t){e.exports="# Issues Resume\r\n\r\n\x3c!-- STORY --\x3e\r\n\r\n### Issue Resume\r\n\r\nIssue Resume represent the top greyed bar, so in order to create this you need\r\nto call in your layout file and pass it :\r\n\r\n1. openNbr the number of opened issues\r\n2. closeNbr the number of closed issues\r\n\r\n```\r\n<IssuesResume openNbr={number of opened issued} closeNbr={number of closed issues}/>\r\n```\r\n"},542:function(e,t){e.exports='# Issues List\r\n\r\n\x3c!-- STORY --\x3e\r\n\r\n### Issue List\r\n\r\nThen if you want a list of issues a the bottom just add a IssueList tag\r\n\r\n```js\r\n<IssuesList tab={[\'1\', \'2\', \'3\']} />\r\n```\r\n\r\ntab is an array you can pass from the layout you call an `<IssuesList />`\r\n\r\n```js\r\ntab={["1", "2", "3"]}\r\n```\r\n\r\nExemple: (From render method of a layout class)\r\n\r\n```js\r\nstate = {\r\n    tab: ["ma valeur 1", "2", "Mon Titre"]\r\n}\r\n\r\n</div>\r\n    <IssuesLayout tab={this.state.tab} />\r\n</div>\r\n```\r\n\r\nYou list will be composed of 3 `<IssueLine>` elements with the title set to the\r\ntext in the tab array\r\n'},543:function(e,t){e.exports="# Issues Line\r\n\r\n\x3c!-- STORY --\x3e\r\n\r\n#### Line\r\n\r\neach line is automaticaly generated from the tab given to a `<IssuesList />`\r\ncomponent. But you can pass them some parameters\r\n\r\n```\r\n<IssuesLine\r\n    status='open' || 'close'\r\n    title=\"My super text\"\r\n    subTitle=\"Sous-titre de l'issue\"\r\n    id={the number of the line}\r\n    key={must be a unique identifier for each line otherwise it will crash (a number is totaly fine)}\r\n/>\r\n```\r\n"},544:function(e,t){e.exports="# SearchBar\r\n\r\n\x3c!-- STORY --\x3e\r\n\r\n#### The Search Bar Component\r\n\r\nBasic Search Bar Component you can use in your header or sidebar.\r\n\r\nTo Call it use:\r\n\r\n```js\r\n<SearchBar />\r\n```\r\n"},545:function(e,t){e.exports='# Icons\r\n\r\n\x3c!-- STORY --\x3e\r\n\r\nExemple of Icon call\r\n\r\n```js\r\n<Icon name=\'close\' color=\'red\' right={0} left={0} size=\'medium\' />\r\n```\r\n\r\nValue that you can pass to an icon\r\n\r\n```\r\ncolor=  every css color or hexdecimal color (default color is green)\r\nright=  {a number representing the right margin}\r\nleft=   {a number representing the left margin}\r\nsize=   "medium" || "small"\r\nname=   "open" || "close" || "filter"\r\nif you dont set the name property the default icon is the github logo\r\n```\r\n'},546:function(e,t){e.exports='# Filters\r\n\r\n\x3c!-- STORY --\x3e\r\n\r\nFilters are component you can add to add filters on a list, like an issues list.\r\n\r\n```js\r\n<Filter name="name of my filter" margin={number}>\r\n```\r\n\r\nBy default margin represent a left margin of 15 if you dont set this parameter.\r\n'},547:function(e,t){e.exports='# Gravatar\r\n\r\n\x3c!-- STORY --\x3e\r\n\r\nThe gravatar is the logo displayed on your github profil.\r\n\r\nIt\'s a 70 x 70 px square image\r\n\r\nYou can call it using:\r\n\r\n```js\r\n<Gravatar src="path to your image">\r\n```\r\n'},548:function(e,t){e.exports="# Issue Status\r\n\r\n\x3c!-- STORY --\x3e\r\n\r\nIssue status block represent the Status of the issue below the title of the\r\nissue in the details layout.\r\n\r\nIssue status accept a status (close || open) and a time in number format which\r\nrepresent the hour or minutes since the issue has been opened.\r\n\r\n```js\r\n<IssuesStatus status='open' time={48} />\r\n```\r\n\r\nIn future version the username will also be passed to this component.\r\n"},549:function(e,t){e.exports='# Issue Header\r\n\r\n\x3c!-- STORY --\x3e\r\n\r\n```js\r\n<IssuesHeader username="username of the user who made this comment">\r\n```\r\n\r\nThe issue header is the top of each new comment made in the issue details view.\r\n\r\nYou can call this component alone but it\'s better if you call it with with an\r\n`<IssuesDetails>`\r\n'},550:function(e,t){e.exports='# Issues Comments\r\n\r\n\x3c!-- STORY --\x3e\r\n\r\nIssues Comments accepts 2 parameters\r\n\r\n1. username of the user that made the comment\r\n2. the text that the user post in the comment\r\n\r\n```js\r\n<IssuesComments username="pseudo of the user" text="Text or comment that the user made on the issue">\r\n```\r\n'},551:function(e,t){e.exports='# Issues Title\r\n\r\n\x3c!-- STORY --\x3e\r\n\r\nHere is a module that is usefull to display the Title of an issue. It always\r\ncome with a new issue button present in the github layout.\r\n\r\nYou can pass the text of the title to this component with the `text=""`\r\nattribut.\r\n\r\n```js\r\n<IssuesTitle text="Text of the title">\r\n```\r\n'},552:function(e,t,n){"use strict";var s=n(5),r=n.n(s),a=n(6),o=n.n(a),i=n(7),c=n.n(i),l=n(8),u=n.n(l),m=n(9),d=n.n(m),p=n(3),h=n.n(p),f=n(4),y=n.n(f),E=n(0),g=n.n(E),v=n(207),S=n(31),O=n(129),x=n(186),b=n(187),I=function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{}),y()(h()(h()(n)),"styles",{marginTop:10}),n}return d()(t,e),o()(t,[{key:"render",value:function(){return g.a.createElement("div",{style:this.styles},g.a.createElement(x.a,{openNbr:this.props.openNbr}),g.a.createElement(b.a,{tab:this.props.tab}))}}]),t}(E.Component),C=I;I.__docgenInfo={description:"",methods:[],displayName:"IssuesLayout"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\components\\issues\\issuesLayout.jsx"]={name:"IssuesLayout",docgenInfo:I.__docgenInfo,path:"src\\components\\issues\\issuesLayout.jsx"});var _=function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{index:0,tab:[]}),y()(h()(h()(n)),"style",{marginTop:10,marginBottom:35}),n}return d()(t,e),o()(t,[{key:"newIssues",value:function(){var e=this.state.tab,t=this.state.index;t+=1,this.setState({index:t}),e.push(t),this.setState({tab:e})}},{key:"render",value:function(){var e=this;return g.a.createElement("div",{style:this.style,className:"container"},g.a.createElement("div",{style:{display:"flex"}},g.a.createElement(O.a,null),g.a.createElement("div",{className:"ml-auto p-2"},g.a.createElement(S.a,{value:"success",text:"New Issue",onClick:function(){return e.newIssues()}}))),g.a.createElement(C,{tab:this.state.tab,openNbr:this.state.index}))}}]),t}(E.Component),T=_;_.__docgenInfo={description:"",methods:[{name:"newIssues",docblock:null,modifiers:[],params:[],returns:null}],displayName:"Container"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\containers\\container.jsx"]={name:"Container",docgenInfo:_.__docgenInfo,path:"src\\containers\\container.jsx"});var R=function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{}),n}return d()(t,e),o()(t,[{key:"render",value:function(){return g.a.createElement(g.a.Fragment,null,g.a.createElement(v.a,null),g.a.createElement(T,null))}}]),t}(E.Component);t.a=R;R.__docgenInfo={description:"",methods:[],displayName:"Layout"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\containers\\layout.jsx"]={name:"Layout",docgenInfo:R.__docgenInfo,path:"src\\containers\\layout.jsx"})},553:function(e,t,n){"use strict";var s=n(5),r=n.n(s),a=n(6),o=n.n(a),i=n(7),c=n.n(i),l=n(8),u=n.n(l),m=n(9),d=n.n(m),p=n(3),h=n.n(p),f=n(4),y=n.n(f),E=n(0),g=n.n(E),v=n(207),S=n(209),O=n(214),x=n(212),b=function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{index:0,tab:[]}),y()(h()(h()(n)),"style",{marginTop:10,marginBottom:35}),n}return d()(t,e),o()(t,[{key:"newIssues",value:function(){alert("New Issue")}},{key:"render",value:function(){return g.a.createElement("div",{style:this.style,className:"container"},g.a.createElement(x.a,{text:"Why Trump is always mean to me, and why does he hates me soo much ?"}),g.a.createElement(S.a,{status:"open",time:48}),g.a.createElement("hr",null),g.a.createElement("div",{className:"row"},g.a.createElement(O.a,{username:"Kim-Jung 1",className:"col"}),g.a.createElement("div",{className:"col col-lg-3 col-md-2"},"SideBar not implemented yet")))}}]),t}(E.Component),I=b;b.__docgenInfo={description:"",methods:[{name:"newIssues",docblock:null,modifiers:[],params:[],returns:null}],displayName:"ContainerDetails"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\containers\\containerDetails.jsx"]={name:"ContainerDetails",docgenInfo:b.__docgenInfo,path:"src\\containers\\containerDetails.jsx"});var C=function(e){function t(){var e,n;r()(this,t);for(var s=arguments.length,a=Array(s),o=0;o<s;o++)a[o]=arguments[o];return n=c()(this,(e=u()(t)).call.apply(e,[this].concat(a))),y()(h()(h()(n)),"state",{}),n}return d()(t,e),o()(t,[{key:"render",value:function(){return g.a.createElement(g.a.Fragment,null,g.a.createElement(v.a,null),g.a.createElement(I,null))}}]),t}(E.Component);t.a=C;C.__docgenInfo={description:"",methods:[],displayName:"Layout"},"undefined"!=typeof STORYBOOK_REACT_CLASSES&&(STORYBOOK_REACT_CLASSES["src\\containers\\layoutDetails.jsx"]={name:"Layout",docgenInfo:C.__docgenInfo,path:"src\\containers\\layoutDetails.jsx"})},554:function(e,t,n){n(215),n(555),e.exports=n(556)},556:function(e,t,n){"use strict";n.r(t),function(e){var t=n(18);n(569);Object(t.configure)(function(){n(570)},e)}.call(this,n(314)(e))},570:function(e,t,n){"use strict";n.r(t),function(e){var t=n(0),s=n.n(t),r=n(18),a=n(44),o=n(21),i=n(552),c=n(536),l=n.n(c),u=n(553),m=n(537),d=n.n(m),p=n(31),h=n(538),f=n.n(h),y=n(130),E=n(539),g=n.n(E),v=n(540),S=n.n(v),O=n(186),x=n(541),b=n.n(x),I=n(187),C=n(542),_=n.n(C),T=n(208),R=n(543),A=n.n(R),B=n(129),j=n(544),w=n.n(j),k=n(30),L=n(545),N=n.n(L),Y=n(45),D=n(546),K=n.n(D),W=n(210),F=n(547),H=n.n(F),M=n(209),z=n(548),G=n.n(z),J=n(211),U=n(549),q=n.n(U),P=n(214),V=n(550),Q=n.n(V),X=n(212),Z=n(551),$=n.n(Z);Object(r.storiesOf)("Layout",e).addDecorator(Object(o.withDocs)(l.a)).add("Issues List",function(){return s.a.createElement("div",null,s.a.createElement(i.a,null))}),Object(r.storiesOf)("Layout",e).addDecorator(Object(o.withDocs)(d.a)).add("Issue details",function(){return s.a.createElement("div",null,s.a.createElement(u.a,null))}),Object(r.storiesOf)("Button",e).addDecorator(Object(o.withDocs)(f.a)).add("Default",function(){return s.a.createElement("div",null,s.a.createElement(p.a,{onClick:Object(a.action)("clicked"),text:"Button",value:"success"}),s.a.createElement(p.a,{style:{margin:10},onClick:Object(a.action)("clicked"),text:"Button",value:"info"}),s.a.createElement(p.a,{onClick:Object(a.action)("clicked"),text:"Button",value:"warning"}),s.a.createElement(p.a,{onClick:Object(a.action)("clicked"),text:"Button",value:"primary"}),s.a.createElement(p.a,{onClick:Object(a.action)("clicked"),text:"Button",value:"dark"}),s.a.createElement(p.a,{onClick:Object(a.action)("clicked"),text:"Button",value:"light"}),s.a.createElement(p.a,{onClick:Object(a.action)("clicked"),text:"Button",value:"secondary"}),s.a.createElement(p.a,{onClick:Object(a.action)("clicked"),text:"Button",value:"danger"}))}),Object(r.storiesOf)("Button",e).addDecorator(Object(o.withDocs)(g.a)).add("With Icon",function(){return s.a.createElement(s.a.Fragment,null,s.a.createElement("div",null,s.a.createElement(y.a,{text:"Button",value:"success",iconName:"open",iconColor:"white"})),s.a.createElement("div",null,s.a.createElement(y.a,{text:"Close",value:"danger",iconName:"close",iconColor:"white"})))}),Object(r.storiesOf)("Issues",e).addDecorator(Object(o.withDocs)(S.a)).add("Default",function(){return s.a.createElement("div",null,s.a.createElement(O.a,null),s.a.createElement(I.a,{tab:["1","2","3"]}))}),Object(r.storiesOf)("Issues",e).addDecorator(Object(o.withDocs)(b.a)).add("Resume",function(){return s.a.createElement("div",null,s.a.createElement(O.a,null))}),Object(r.storiesOf)("Issues",e).addDecorator(Object(o.withDocs)(G.a)).add("Status",function(){return s.a.createElement("div",null,s.a.createElement(M.a,{status:"open",time:32}))}),Object(r.storiesOf)("Issues",e).addDecorator(Object(o.withDocs)($.a)).add("Title",function(){return s.a.createElement("div",null,s.a.createElement(X.a,{text:"Why Trump is always mean to me, and why does he hates me soo much ?"}))}),Object(r.storiesOf)("Issues",e).addDecorator(Object(o.withDocs)(q.a)).add("Header",function(){return s.a.createElement("div",null,s.a.createElement(J.a,{username:"Kim-Jung 1"}))}),Object(r.storiesOf)("Issues",e).addDecorator(Object(o.withDocs)(Q.a)).add("Comments",function(){return s.a.createElement("div",null,s.a.createElement(P.a,{username:"thomas"}))}),Object(r.storiesOf)("Issues",e).addDecorator(Object(o.withDocs)(_.a)).add("List",function(){return s.a.createElement("div",null,s.a.createElement(I.a,{tab:["1","2","3"]}))}),Object(r.storiesOf)("Issues",e).addDecorator(Object(o.withDocs)(A.a)).add("Line",function(){return s.a.createElement("div",null,s.a.createElement(T.a,null))}),Object(r.storiesOf)("SearchBar",e).addDecorator(Object(o.withDocs)(w.a)).add("Default",function(){return s.a.createElement("div",null,s.a.createElement(B.a,null))}),Object(r.storiesOf)("Gravatar",e).addDecorator(Object(o.withDocs)(H.a)).add("Default",function(){return s.a.createElement("div",null,s.a.createElement(W.a,{src:"../img/avatar.png"}))}),Object(r.storiesOf)("Icon",e).addDecorator(Object(o.withDocs)(N.a)).add("Default",function(){return s.a.createElement("div",null,s.a.createElement(k.a,{name:"open",color:"red",right:0,left:0,size:"medium"}))}),Object(r.storiesOf)("Filter",e).addDecorator(Object(o.withDocs)(K.a)).add("Default",function(){return s.a.createElement("div",null,s.a.createElement(Y.a,null))})}.call(this,n(314)(e))}},[[554,2,4]]]);
//# sourceMappingURL=iframe.0f29144e51218adc79e3.bundle.js.map