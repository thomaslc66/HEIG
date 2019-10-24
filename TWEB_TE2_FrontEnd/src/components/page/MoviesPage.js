import React, { Component } from 'react';
import axios from 'axios';
import { apiUrl, apiKey } from '../../utils/config';

class MoviePage extends Component {
  state = {
    page: 1,
    movie: []
  };

  componentDidMount = () => {
    this.setState({ movie: [] });
    // Trop beau
    this.loadMovies(this.state.page);
    this.loadMovies(this.state.page + 1);
  };

  nextMovies = page => {
    this.loadMovies(this.state.page);
  };

  constructApiUrl = page => {
    return `${apiUrl}/popular?page=${page}&api_key=${apiKey}`;
  };

  loadMovies = page => {
    let moviesArr = this.state.movie;

    axios.get(this.constructApiUrl(page)).then(response => {
      console.log(response.data.results);
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
    this.loadMovies(this.state.page);
    return (
      <React.Fragment>
        <h1>Welcome to Movie Theather</h1>
        <ul>
          {this.state.movie.map(mov => {
            const posterUrl = `https://image.tmdb.org/t/p/w500/${mov.image}`;
            return (
              <div key={mov.title}>
                <div>
                  {mov.title} - date: {mov.release_date}
                </div>
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
      </React.Fragment>
    );
  }
}

export default MoviePage;
