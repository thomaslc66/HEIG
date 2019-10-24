import React from 'react';
import { storiesOf } from '@storybook/react';
import { action } from '@storybook/addon-actions';
import { withDocs } from 'storybook-readme';

import Layout from '../containers/layout';
import LayoutREADME from '../containers/layoutREADME.md';

import LayoutDetails from '../containers/layoutDetails';
import LayoutDetailsREADME from '../containers/layoutDetailsREADME.md';

import Button from '../components/buttons/button';
import ButtonREADME from '../components/buttons/README.md';

import ButtonWithIcon from '../components/buttons/buttonWithIcon';
import ButtonWithIconREADME from '../components/buttons/buttonWithIconREADME.md';

import IssuesREADME from '../components/issues/Readme/README.md';

import IssuesResume from '../components/issues/issuesResume';
import IssuesResumeREADME from '../components/issues/Readme/issuesResumeREADME.md';

import IssuesList from '../components/issues/issuesList';
import IssuesListREADME from '../components/issues/Readme/issuesListREADME.md';

import IssuesLine from '../components/issues/issuesLine';
import IssuesLineREADME from '../components/issues/Readme/issuesLineREADME.md';

import SearchBar from '../components/bar/searchBar';
import SearchBarREADME from '../components/bar/README.md';

import Icon from '../components/glyphicon/icon';
import IconREADME from '../components/glyphicon/iconREADME.md';

import Filter from '../components/Filters/filter';
import FilterREADME from '../components/Filters/filterREADME.md';

import Gravatar from '../components/glyphicon/gravatar';
import GravatarREADME from '../components/glyphicon/gravatarREADME.md';

import IssuesStatus from '../components/issues/issuesStatus';
import IssuesStatusREADME from '../components/issues/Readme/issuesStatusREADME.md';

import IssuesHeader from '../components/issues/issuesHeader';
import IssuesHeaderREADME from '../components/issues/Readme/issuesHeaderREADME.md';

import IssuesComments from '../components/issues/issuesComments';
import IssuesCommentsREADME from '../components/issues/Readme/issuesCommentsREADME.md';

import IssuesTitle from '../components/issues/issuesTitle';
import IssuesTitleREADME from '../components/issues/Readme/issuesTitleREADME.md';

storiesOf('Layout', module)
  .addDecorator(withDocs(LayoutREADME))
  .add('Issues List', () => {
    return (
      <div>
        <Layout />
      </div>
    );
  });

storiesOf('Layout', module)
  .addDecorator(withDocs(LayoutDetailsREADME))
  .add('Issue details', () => {
    return (
      <div>
        <LayoutDetails />
      </div>
    );
  });

storiesOf('Button', module)
  .addDecorator(withDocs(ButtonREADME))
  .add('Default', () => {
    return (
      <div>
        <Button onClick={action('clicked')} text='Button' value='success' />
        <Button
          style={{ margin: 10 }}
          onClick={action('clicked')}
          text='Button'
          value='info'
        />
        <Button onClick={action('clicked')} text='Button' value='warning' />
        <Button onClick={action('clicked')} text='Button' value='primary' />
        <Button onClick={action('clicked')} text='Button' value='dark' />
        <Button onClick={action('clicked')} text='Button' value='light' />
        <Button onClick={action('clicked')} text='Button' value='secondary' />
        <Button onClick={action('clicked')} text='Button' value='danger' />
      </div>
    );
  });

storiesOf('Button', module)
  .addDecorator(withDocs(ButtonWithIconREADME))
  .add('With Icon', () => {
    return (
      <React.Fragment>
        <div>
          <ButtonWithIcon
            text='Button'
            value='success'
            iconName='open'
            iconColor='white'
          />
        </div>
        <div>
          <ButtonWithIcon
            text='Close'
            value='danger'
            iconName='close'
            iconColor='white'
          />
        </div>
      </React.Fragment>
    );
  });

storiesOf('Issues', module)
  .addDecorator(withDocs(IssuesREADME))
  .add('Default', () => {
    return (
      <div>
        <IssuesResume />
        <IssuesList tab={['1', '2', '3']} />
      </div>
    );
  });

storiesOf('Issues', module)
  .addDecorator(withDocs(IssuesResumeREADME))
  .add('Resume', () => {
    return (
      <div>
        <IssuesResume />
      </div>
    );
  });

storiesOf('Issues', module)
  .addDecorator(withDocs(IssuesStatusREADME))
  .add('Status', () => {
    return (
      <div>
        <IssuesStatus status='open' time={32} />
      </div>
    );
  });

storiesOf('Issues', module)
  .addDecorator(withDocs(IssuesTitleREADME))
  .add('Title', () => {
    return (
      <div>
        <IssuesTitle text='Why Trump is always mean to me, and why does he hates me soo much ?' />
      </div>
    );
  });

storiesOf('Issues', module)
  .addDecorator(withDocs(IssuesHeaderREADME))
  .add('Header', () => {
    return (
      <div>
        <IssuesHeader username='Kim-Jung 1' />
      </div>
    );
  });

storiesOf('Issues', module)
  .addDecorator(withDocs(IssuesCommentsREADME))
  .add('Comments', () => {
    return (
      <div>
        <IssuesComments username='thomas' />
      </div>
    );
  });

storiesOf('Issues', module)
  .addDecorator(withDocs(IssuesListREADME))
  .add('List', () => {
    return (
      <div>
        <IssuesList tab={['1', '2', '3']} />
      </div>
    );
  });

storiesOf('Issues', module)
  .addDecorator(withDocs(IssuesLineREADME))
  .add('Line', () => {
    return (
      <div>
        <IssuesLine />
      </div>
    );
  });

storiesOf('SearchBar', module)
  .addDecorator(withDocs(SearchBarREADME))
  .add('Default', () => {
    return (
      <div>
        <SearchBar />
      </div>
    );
  });

storiesOf('Gravatar', module)
  .addDecorator(withDocs(GravatarREADME))
  .add('Default', () => {
    return (
      <div>
        <Gravatar src='../img/avatar.png' />
      </div>
    );
  });

storiesOf('Icon', module)
  .addDecorator(withDocs(IconREADME))
  .add('Default', () => {
    return (
      <div>
        <Icon name='open' color='red' right={0} left={0} size='medium' />
      </div>
    );
  });

storiesOf('Filter', module)
  .addDecorator(withDocs(FilterREADME))
  .add('Default', () => {
    return (
      <div>
        <Filter />
      </div>
    );
  });
