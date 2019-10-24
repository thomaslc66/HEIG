import React, { Component } from 'react';
import { AuthContext } from '../../providers/AuthProvider';
import { Button } from 'antd';
import axios from 'axios';
import { Link } from 'react-router-dom';
import { apiUrl, apiKey } from '../../utils/config';

class UpComing extends Component {
  state = {
    page: 1,
    movie: []
  };

  componentDidMount = () => {
    this.setState({ movie: [] });
    this.loadMovies(this.state.page);
  };

  nextMovies = () => {
    const incrPage = this.state.page + 1;
    this.setState({ page: incrPage }, () => {
      //in a function to have the new state
      this.loadMovies(this.state.page);
    });
  };

  constructApiUrl = page => {
    return `${apiUrl}/upcoming?page=${page}&api_key=${apiKey}`;
  };

  loadMovies = page => {
    let moviesArr = this.state.movie;
    axios.get(this.constructApiUrl(page)).then(response => {
      response.data.results.map(movie =>
        moviesArr.push({
          title: movie.title,
          date: movie.release_date,
          image: movie.poster_path
        })
      );
      this.setState({ movie: moviesArr });
    });
  };

  render() {
    return (
      <AuthContext>
        {({ signOut }) => (
          <React.Fragment>
            <h1>Next Week on Movie Theather</h1>
            <Link to='/'>All movie List</Link>
            <ul>
              {this.state.movie.map(mov => {
                const posterUrl = `https://image.tmdb.org/t/p/w500/${
                  mov.image
                }`;
                return (
                  <div key={mov.title}>
                    <div>{mov.title}</div>
                    <img
                      src={posterUrl}
                      alt={mov.title}
                      height={200}
                      width='auto'
                    />
                  </div>
                );
              })}
            </ul>
            <Button onClick={this.nextMovies}>Load More Movies</Button>
          </React.Fragment>
        )}
      </AuthContext>
    );
  }
}

export default UpComing;
