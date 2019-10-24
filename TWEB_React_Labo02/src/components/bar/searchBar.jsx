import React, { Component } from "react";
import Button from "../buttons/button";
import Filter from "../Filters/filter";

class SearchBar extends Component {
  state = {};

  render() {
    return (
      <form className="form-inline">
        <Button value="light" text={<Filter />} />
        <input
          className="form-control mr-sm-2"
          type="search"
          placeholder="is:issue is:open"
        />
        <button className="btn btn-outline-succes my-sm-0" type="submit">
          Search
        </button>
      </form>
    );
  }
}

export default SearchBar;
