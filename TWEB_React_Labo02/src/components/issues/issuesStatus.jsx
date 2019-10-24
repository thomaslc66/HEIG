import React, { Component } from 'react';
import ButtonWithIcon from '../buttons/buttonWithIcon';

class IssuesStatus extends Component {
  state = {
    time: this.props.time || 0
  };

  iconButton() {
    if (this.props.status === 'close') {
      return (
        <ButtonWithIcon
          iconName='close'
          text='Closed'
          value='danger'
          iconColor='white'
        />
      );
    } else {
      return (
        <ButtonWithIcon
          iconName='open'
          text='Open'
          value='success'
          iconColor='white'
        />
      );
    }
  }

  render() {
    return (
      <div
        style={{
          display: 'flex',
          marginBottom: 30,
          alignItems: 'center'
        }}>
        {this.iconButton()}
        <h6 style={{ marginLeft: 30, color: 'gray' }}>
          Kim-Jung 1 opened this issue {this.state.time}h ago
        </h6>
      </div>
    );
  }
}

export default IssuesStatus;
