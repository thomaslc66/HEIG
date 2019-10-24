import React, { Component } from 'react';
import Button from '../buttons/button';

class IssuesTitle extends Component {
  state = {};
  render() {
    return (
      <div style={{ display: 'flex', textAlign: 'left' }}>
        <h1>{this.props.text}</h1>
        <div className='ml-auto p-2'>
          <Button value='success' text='New Issue' />
        </div>
      </div>
    );
  }
}

export default IssuesTitle;
