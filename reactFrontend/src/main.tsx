import React from 'react'
import ReactDOM from 'react-dom/client'
import {
  createBrowserRouter,
  RouterProvider,
} from "react-router-dom";

import './index.css'
import Root from './routes/Root';
import ErrorPage from './routes/ErrorPage';
import SearchCraftsmenPage from './routes/SearchCraftsmenPage';
import RankedCraftsmenPage from './routes/RankedCraftsmenPage';
import UpdateCraftsmenPage from './routes/UpdateCraftsmenPage';
import SelectCraftsmenForUpdatePage from './routes/SelectCraftsmenForUpdatePage';
import { searchCraftsmenAction } from './functions/searchCraftsmenAction';

const router = createBrowserRouter([
  {
    path: "/",
    element: <Root />,
    errorElement: <ErrorPage />,
  },
  {
    // Page for searching craftsmen by postcode
    path: "craftsmen/search",
    element: <SearchCraftsmenPage/>,
    errorElement: <ErrorPage />,
    action: searchCraftsmenAction,
  },
  {
    // Page for displaying ranked craftsmen
    path: "craftsmen/search/:postcode",
    element: <RankedCraftsmenPage />,
  },
  {
    // Page for selecting the craftsman to update
    path: "craftsmen/update",
    element: <SelectCraftsmenForUpdatePage />,
  },
  {
    // Page for updating craftsmen attributes
    path: "craftsmen/update/:id",
    element: <UpdateCraftsmenPage />,
  },
]);

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <RouterProvider router={router} />
  </React.StrictMode>,
)
