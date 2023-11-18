import { useRouteError } from "react-router-dom";
import NavBar from "../components/NavBar";

// Page to display when an error occurs
export default function ErrorPage() {
  const error = useRouteError() as { statusText?: string; message?: string };
  // log the error to the console in development mode
  if (import.meta.env.DEV) {
    console.error(error);
  }

  return (
    <>
      <div id="error-page">
        <h1>Oops!</h1>
        <p>Sorry, an unexpected error has occurred.</p>
        <p>
          <i>{error.statusText || error.message}</i>
        </p>
      </div>
      <NavBar />
    </>
  );
}
