import React, { Component } from 'react';

class Gravatar extends Component {
  state = {};

  styles = {
    verticalAlign: 'middle',
    height: 70,
    weight: 70
  };

  render() {
    return <img style={this.styles} alt='avatar' src={this.props.src} />;
  }
}

export default Gravatar;
