import React, { Component } from 'react';

import IssuesStatus from '../components/issues/issuesStatus';
import IssuesComments from '../components/issues/issuesComments';
import IssuesTitle from '../components/issues/issuesTitle';

class ContainerDetails extends Component {
  state = {
    index: 0,
    tab: []
  };

  style = {
    marginTop: 10,
    marginBottom: 35
  };

  newIssues() {
    alert('New Issue');
  }

  render() {
    return (
      <div style={this.style} className='container'>
        {/* Issue Title */}
        <IssuesTitle text='Why Trump is always mean to me, and why does he hates me soo much ?' />
        {/* Issue Status */}
        <IssuesStatus status='open' time={48} />
        <hr />
        {/* Issue Details and Gravatar */}
        <div className='row'>
          <IssuesComments username='Kim-Jung 1' className='col' />
          <div className='col col-lg-3 col-md-2'>
            SideBar not implemented yet
          </div>
        </div>
      </div>
    );
  }
}

export default ContainerDetails;
