import React from 'react'
import ReactDOM from 'react-dom/client'
import {
  createBrowserRouter,
  RouterProvider,
} from "react-router-dom";

import './index.css'
import Root from './routes/Root';
import ErrorPage from './routes/ErrorPage';
import SearchCraftsmenByPostcodePage from './routes/SearchCraftsmenByPostcodePage';
import RankedCraftsmenPage from './routes/RankedCraftsmenPage';
import UpdateCraftsmenPage from './routes/UpdateCraftsmenPage';
import SelectCraftsmenById from './routes/SelectCraftsmenById';
import { searchPostcodesAction } from './functions/searchPostcodesAction';
import { searchCraftsmenAction } from './functions/searchCraftsmenAction';

const router = createBrowserRouter([
  {
    path: "/",
    element: <Root />,
    errorElement: <ErrorPage />,
  },
  {
    // Page for searching craftsmen by postcode
    path: "/craftsmen/search",
    element: <SearchCraftsmenByPostcodePage/>,
    errorElement: <ErrorPage />,
    action: searchPostcodesAction,
  },
  {
    // Page for displaying ranked craftsmen
    path: "/craftsmen/search/:postcode",
    element: <RankedCraftsmenPage />,
    errorElement: <ErrorPage />,
  },
  {
    // Page for selecting the craftsman to update
    path: "/craftsmen/update",
    element: <SelectCraftsmenById />,
    errorElement: <ErrorPage />,
    action: searchCraftsmenAction,
  },
  {
    // Page for updating craftsmen attributes
    path: "/craftsmen/update/:id",
    element: <UpdateCraftsmenPage />,
    errorElement: <ErrorPage />,
  },
]);

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <RouterProvider router={router} />
  </React.StrictMode>,
)
