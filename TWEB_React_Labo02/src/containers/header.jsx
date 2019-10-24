import React, { Component } from 'react';
import SearchBar from './../components/bar/searchBar';
import Icon from '../components/glyphicon/icon';

class Header extends Component {
  state = {
    title: 'Github'
  };
  render() {
    return (
      <nav className='navbar navbar-expand-lg navbar-dark bg-dark'>
        <div className='container'>
          <div>
            <Icon size='medium' color='white' />
            <a className='navbar-brand' href='/' style={{ marginLeft: 10 }}>
              {this.state.title}
            </a>
          </div>
          <SearchBar />
        </div>
      </nav>
    );
  }
}

export default Header;
