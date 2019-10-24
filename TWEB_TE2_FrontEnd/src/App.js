import React, { Component } from 'react';
import { Switch, Route } from 'react-router-dom';
import LoginPage from './components/page/LoginPage';
import HomePage from './components/page/HomePage';
import ProtectedRoute from './components/ProtectedRoute';
import MoviePage from './components/page/MoviesPage';
import UpComing from './components/page/UpComing';

import 'antd/dist/antd.css';
import './App.css';

class App extends Component {
  render() {
    return (
      <Switch>
        <ProtectedRoute path='/' exact component={HomePage} />
        <ProtectedRoute path='/upcoming' component={UpComing} />
        <Route path='/movies' component={MoviePage} />
        <Route path='/login' component={LoginPage} />
      </Switch>
    );
  }
}

export default App;
