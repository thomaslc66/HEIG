import React, { Component } from 'react';
import Gravatar from '../glyphicon/gravatar';
import IssuesHeader from './issuesHeader';
import IssuesDetails from './issuesDetails';

class IssuesComments extends Component {
  state = {};
  render() {
    return (
      <div className='col'>
        <div className='row'>
          <div style={{ marginRight: 20 }} className='col-lg-1 col-md-1'>
            <Gravatar src='/img/avatar.png' />
          </div>
          <div className='col col-md col-sm'>
            <IssuesHeader username={this.props.username} />
            <IssuesDetails text={this.props.text} />
          </div>
        </div>
      </div>
    );
  }
}

export default IssuesComments;
