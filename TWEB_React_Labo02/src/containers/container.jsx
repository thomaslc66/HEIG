import React, { Component } from 'react';

import Button from './../components/buttons/button';
import SearchBar from './../components/bar/searchBar';
import IssuesLayout from './../components/issues/issuesLayout';

class Container extends Component {
  state = {
    index: 0,
    tab: []
  };

  style = {
    marginTop: 10,
    marginBottom: 35
  };

  newIssues() {
    //alert("New Issue");
    let array = this.state.tab;
    let index = this.state.index;
    index += 1;
    this.setState({ index: index });
    array.push(index);
    this.setState({ tab: array });
  }

  render() {
    return (
      <div style={this.style} className='container'>
        <div style={{ display: 'flex' }}>
          <SearchBar />
          <div className='ml-auto p-2'>
            <Button
              value='success'
              text='New Issue'
              onClick={() => this.newIssues()}
            />
          </div>
        </div>
        <IssuesLayout tab={this.state.tab} openNbr={this.state.index} />
      </div>
    );
  }
}

export default Container;
