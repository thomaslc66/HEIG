import React, { Component } from 'react';

class IssuesDetails extends Component {
  state = {};

  render() {
    return (
      <ul className='list-group'>
        <li className='list-group-item'>
          <div style={{ textAlign: 'left' }}>
            {this.props.text}
            {/* This text is only for demo purpose */}
            Hello every body, I'm currently dealing with a painfull situation.
            <br />
            I've been playing with some of my fireworks in my garden, because i
            really like big fireworks. It's not always intentional but you know
            sometime fireworks are not really precise when we throw them. And i
            don't know why but a lot of other countries are afraid. I'm only
            having fun with some of my friends. The Us president Trumpy Trump
            always call me to stop my game and tell me i'm childish and that i
            need to grow up. Even the French President Maccaron call me
            sometimes.
            <br />
            <br />I don't know what's bother them so much, i don't tell them
            anything an 4 or 14 july. What's the big deal if i'm playing ?? Ok
            sometimes some of my fireworks are nuclear but it's because i have a
            lot of them so sometimes i can mix them up.
            <br />
            <br />
            Can you help me finding a solution to make them understand my point
            of view?
          </div>
        </li>
      </ul>
    );
  }
}

export default IssuesDetails;
