import React from 'react'
import ReactDOM from 'react-dom/client'
import {
  createBrowserRouter,
  RouterProvider,
} from "react-router-dom";

import './index.css'
import Root from './routes/Root';
import ErrorPage from './routes/ErrorPage';
import SearchPage from './routes/SearchPage';

const router = createBrowserRouter([
  {
    path: "/",
    element: <Root />,
    errorElement: <ErrorPage />,
  },
  {
    path: "craftsmen/search",
    element: <SearchPage/>,
    errorElement: <ErrorPage />,
  },
  {
    path: "craftsmen/search/:postcode",
    // TODO
    element: <Root />,
  },
  {
    path: "craftsmen/update/:id",
    // TODO
    element: <Root />,
  },
]);

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <RouterProvider router={router} />
  </React.StrictMode>,
)
