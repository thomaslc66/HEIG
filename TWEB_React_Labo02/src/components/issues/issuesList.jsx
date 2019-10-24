import React, { Component } from 'react';
import IssuesLine from './issuesLine';

class IssuesList extends Component {
  state = {
    tabs: this.props.tab
  };

  renderIssueId(id) {
    let tab = "Super titre de mon problème avec numérotation de l'issue N°";
    return (tab += id);
  }

  render() {
    return (
      <ul className='list-group'>
        {this.state.tabs.map(tab => (
          <IssuesLine
            status='open'
            title={this.renderIssueId(tab)}
            subTitle={"Sous-titre de l'issue"}
            id={tab}
            key={tab}
          />
        ))}
      </ul>
    );
  }
}

export default IssuesList;
