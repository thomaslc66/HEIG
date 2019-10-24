import React, { Component } from 'react';
import Header from './header';
import ContainerDetails from './containerDetails';

class Layout extends Component {
  state = {};

  render() {
    return (
      <React.Fragment>
        <Header />
        <ContainerDetails />
      </React.Fragment>
    );
  }
}

export default Layout;
