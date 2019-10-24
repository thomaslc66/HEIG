import React, { Component } from 'react';
import axios from 'axios';
import { url } from '../utils/config';

const {
  Provider: AuthContextProvider,
  Consumer: AuthContext
} = React.createContext();

class AuthProvider extends Component {
  constructor(props) {
    super(props);
    this.state = {
      user: null,
      signIn: this.signIn,
      signOut: this.signOut,
      error: null
    };
  }

  componentDidMount = () => {
    const token = localStorage.getItem('jwt-token');
    if (token) {
      axios
        .get(`${url}/me`, {
          headers: { Authorization: `bearer ${token}` }
        })
        .then(response => {
          const { user } = response.data;
          this.setState({ user });
        })
        .catch(err => {
          localStorage.removeItem('jwt-token');
        });
    }
  };

  signIn = ({ userName, password }) => {
    //Sign in user
    axios
      .post(`${url}/auth/login`, {
        login: userName,
        password: password
      })
      .then(response => {
        const { user, token } = response.data;
        this.setState({ user });
        localStorage.setItem('jwt-token', token);
      })
      .catch(error => {
        this.setState({ error: 'Invalid login or password' });
      });
  };

  signOut = () => {
    //Sign Out user
    console.log('dans signOut');
    localStorage.removeItem('jwt-token');
    // location.reload()
    this.setState({ user: null });
  };

  render() {
    const { children } = this.props;
    return (
      <AuthContextProvider value={this.state}>{children}</AuthContextProvider>
    );
  }
}

export { AuthContext };
export default AuthProvider;
