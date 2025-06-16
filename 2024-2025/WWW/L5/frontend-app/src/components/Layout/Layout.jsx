import React from 'react';
import { Outlet } from 'react-router-dom';
import Navigation from 'Navigation';

const Layout = () => {
  return (
    <>
      <Navigation />
      <main className="main-content">
        <Outlet />
      </main>
    </>
  );
};

export default Layout;
