import React, { Component } from 'react';
import Icon from '../glyphicon/icon';

class IssuesLine extends Component {
  state = {
    title: this.props.title || 'Titre par default',
    subTitle: this.props.subTitle || 'Sous-titre par default'
  };

  stylesRow = {
    textAlign: 'left',
    display: 'flex',
    flexDirection: 'row',
    justifyContent: 'left'
  };

  styleColumns = {
    marginLeft: 15
  };

  render() {
    return (
      <li className='list-group-item list-group-item-action'>
        <div style={this.stylesRow}>
          <Icon name={this.props.status} />
          <div style={this.styleColumns} classname='container'>
            <div classname='row'>
              <h4>{this.state.title} </h4>
            </div>
            <div classname='row'>
              <h8>{this.state.subTitle}</h8>
            </div>
          </div>
        </div>
      </li>
    );
  }
}

export default IssuesLine;
