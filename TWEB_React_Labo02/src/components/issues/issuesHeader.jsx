import React, { Component } from 'react';
import Icon from '../glyphicon/icon';
import Filter from '../Filters/filter';

class IssuesHeader extends Component {
  state = {
    open: this.props.index,
    close: this.props.closeNbr || 0,
    margin: 25
  };

  styles = {
    display: 'flex',
    justifyContent: 'space-between'
  };

  divStyleOpen = {
    marginLeft: 15,
    fontWeight: 'bold'
  };

  divStyle = {
    marginLeft: 15
  };

  render() {
    return (
      <li
        style={this.styles}
        className='list-group-item list-group-item-secondary'>
        <div style={this.styles}>
          {this.props.username} commented 11 hours ago
        </div>
        <div style={this.styles}>...</div>
      </li>
    );
  }
}

export default IssuesHeader;
