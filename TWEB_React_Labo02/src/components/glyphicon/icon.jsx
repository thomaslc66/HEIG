import React, { Component } from "react";
import Octicon, {
  IssueOpened,
  Check,
  TriangleDown,
  MarkGithub
} from "@githubprimer/octicons-react";

class Icon extends Component {
  state = {
    green: "#28a745",
    open: IssueOpened,
    close: Check,
    filter: TriangleDown,
    github: MarkGithub
  };

  styles = {
    color: this.props.color || this.state.green,
    marginRight: this.props.right || 0,
    marginLeft: this.props.left || 0
  };

  selectIcon() {
    let value;
    switch (this.props.name) {
      case "open":
        value = this.state.open;
        break;
      case "close":
        value = this.state.close;
        break;
      case "filter":
        value = this.state.filter;
        break;
      default:
        value = this.state.github;
        break;
    }

    return value;
  }

  render() {
    return (
      <span style={this.styles}>
        <Octicon
          icon={this.selectIcon()}
          verticalAlign="middle"
          size={this.props.size}
        />
      </span>
    );
  }
}

export default Icon;
