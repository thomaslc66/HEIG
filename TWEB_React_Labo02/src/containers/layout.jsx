import React, { Component } from "react";
import Header from "./header";
import Container from "./container";

class Layout extends Component {
  state = {};

  render() {
    return (
      <React.Fragment>
        <Header />
        <Container />
      </React.Fragment>
    );
  }
}

export default Layout;
