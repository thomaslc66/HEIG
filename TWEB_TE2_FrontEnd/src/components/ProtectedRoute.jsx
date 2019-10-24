import React, { Component } from 'react';
import { Route, Redirect } from 'react-router-dom';
import { AuthContext } from '../providers/AuthProvider';

class ProtectedRoute extends Component {
  state = {};

  render() {
    const { component, ...rest } = this.props;
    const Component = component;

    return (
      <AuthContext>
        {({ user }) => {
          return user ? (
            <Route {...rest} render={params => <Component {...params} />} />
          ) : (
            <Redirect to='/login' />
          );
        }}
      </AuthContext>
    );
  }
}

export default ProtectedRoute;
