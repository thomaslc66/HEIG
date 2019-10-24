import React, { Component } from 'react';
import Icon from '../glyphicon/icon';

class Filter extends Component {
  state = {};

  styles = {
    marginLeft: this.props.margin || 15
  };

  render() {
    return (
      <div style={this.styles}>
        {this.props.name || 'Filters'}
        <Icon name='filter' color='gray' left={5} />
      </div>
    );
  }
}

export default Filter;
