import React, { Component } from 'react';
import IssuesResume from './issuesResume';
import IssuesList from './issuesList';

class IssuesLayout extends Component {
  state = {};

  styles = {
    marginTop: 10
  };

  render() {
    return (
      <div style={this.styles}>
        <IssuesResume openNbr={this.props.openNbr} />
        <IssuesList tab={this.props.tab} />
      </div>
    );
  }
}

export default IssuesLayout;
