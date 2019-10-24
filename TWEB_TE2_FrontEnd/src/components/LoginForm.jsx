import React, { Component } from 'react';
import { Form, Icon, Input, Button } from 'antd';
import { Redirect } from 'react-router-dom';
import { AuthContext } from '../providers/AuthProvider';
//import axios from 'axios';

class LoginForm extends Component {
  state = {};

  style = {
    color: 'red'
  };

  render() {
    const { getFieldDecorator } = this.props.form;

    return (
      <AuthContext>
        {({ error, user, signIn }) => {
          if (user) {
            return <Redirect to='/' />;
          }

          const handleSubmit = e => {
            e.preventDefault();
            this.props.form.validateFields((err, values) => {
              if (!err) {
                const { userName, password } = values;
                signIn({ userName, password });
              } else {
                console.log('Erreur: ', err);
              }
            });
          };
          return (
            <React.Fragment>
              <h1>Login</h1>
              <div style={this.style}>{error}</div>
              <Form onSubmit={handleSubmit} className='login-form'>
                <Form.Item>
                  {getFieldDecorator('userName', {
                    rules: [
                      { required: true, message: 'Please input your username!' }
                    ]
                  })(
                    <Input
                      prefix={
                        <Icon
                          type='user'
                          style={{ color: 'rgba(0,0,0,.25)' }}
                        />
                      }
                      placeholder='Username'
                    />
                  )}
                </Form.Item>
                <Form.Item>
                  {getFieldDecorator('password', {
                    rules: [
                      { required: true, message: 'Please input your Password!' }
                    ]
                  })(
                    <Input
                      prefix={
                        <Icon
                          type='lock'
                          style={{ color: 'rgba(0,0,0,.25)' }}
                        />
                      }
                      type='password'
                      placeholder='Password'
                    />
                  )}
                </Form.Item>
                <Form.Item>
                  <Button
                    type='primary'
                    htmlType='submit'
                    className='login-form-button'>
                    Log in
                  </Button>
                  <div>
                    Or <a href='/register'>register now!</a>
                  </div>
                </Form.Item>
              </Form>
            </React.Fragment>
          );
        }}
      </AuthContext>
    );
  }
}

const LoginFormComponent = Form.create()(LoginForm);

export { LoginFormComponent as default };
