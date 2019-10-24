import React, { Component } from 'react';
import Icon from '../glyphicon/icon';

class Button extends Component {
  state = {
    text: this.props.text,
    value: this.props.value
  };

  styles = {
    fontWeight: this.props.fontWeight
  };

  render() {
    return (
      <button
        style={this.styles}
        type='button'
        className={this.renderClasses()}
        onClick={this.props.onClick}>
        {this.props.text}
      </button>
    );
  }

  renderClasses() {
    let classes = 'btn btn-';
    return (classes += this.state.value);
  }
}

export default Button;
