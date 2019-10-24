import React, { Component } from 'react';
import Icon from '../glyphicon/icon';
import Filter from '../Filters/filter';

class IssuesResume extends Component {
  state = {
    open: this.props.openNbr || 0,
    close: this.props.closeNbr || 0,
    margin: 25
  };

  styles = {
    display: 'flex',
    justifyContent: 'space-between'
  };

  divStyleOpen = {
    marginLeft: 10,
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
          <Icon name='open' />
          <div style={this.divStyleOpen}>{this.props.openNbr || 0} Open</div>
          <div style={this.divStyle}>
            <Icon name='close' color='red' /> {this.state.close} Closed
          </div>
        </div>
        <div style={this.styles}>
          <Filter name='Author' />
          <Filter name='Labels' />
          <Filter name='Projects' />
          <Filter name='Milestones' />
          <Filter name='Assignee' />
          <Filter name='Sort' />
        </div>
      </li>
    );
  }
}

export default IssuesResume;
