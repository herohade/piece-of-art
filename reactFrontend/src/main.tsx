import React from "react";
import ReactDOM from "react-dom/client";
import { createBrowserRouter, RouterProvider } from "react-router-dom";

import "./css/index.css";
import Root from "./routes/Root";
import ErrorPage from "./routes/ErrorPage";
import SearchCraftsmenByPostcodePage from "./routes/SearchCraftsmenByPostcodePage";
import RankedCraftsmenPage from "./routes/RankedCraftsmenPage";
import UpdateCraftsmenPage from "./routes/UpdateCraftsmenPage";
import SelectCraftsmenById from "./routes/SelectCraftsmenById";
import { searchPostcodesAction } from "./functions/searchPostcodesAction";
import { searchCraftsmenAction } from "./functions/searchCraftsmenAction";
import { updateCraftsmenAction } from "./functions/updateCraftsmenAction";
import { loadMoreCraftsmen } from "./functions/loadMoreCraftsmen";

const router = createBrowserRouter([
  {
    path: "/",
    element: <Root />,
    errorElement: <ErrorPage />,
  },
  {
    // Page for searching craftsmen by postcode
    path: "/search",
    element: <SearchCraftsmenByPostcodePage />,
    errorElement: <ErrorPage />,
    action: searchPostcodesAction,
  },
  {
    // Page for displaying ranked craftsmen
    path: "/search/:postcode",
    element: <RankedCraftsmenPage />,
    errorElement: <ErrorPage />,
    action: loadMoreCraftsmen,
  },
  {
    // Page for selecting the craftsman to update
    path: "/update",
    element: <SelectCraftsmenById />,
    errorElement: <ErrorPage />,
    action: searchCraftsmenAction,
  },
  {
    // Page for updating craftsmen attributes
    path: "/update/:id",
    element: <UpdateCraftsmenPage />,
    errorElement: <ErrorPage />,
    action: updateCraftsmenAction,
  },
]);

ReactDOM.createRoot(document.getElementById("root")!).render(
  <React.StrictMode>
    <RouterProvider router={router} />
  </React.StrictMode>
);
