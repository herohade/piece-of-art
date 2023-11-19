import { redirect } from "react-router-dom";

export async function loadMoreCraftsmen({
  params,
  request,
}: {
  params: { postcode?: number };
  request: Request;
}) {
  const { postcode } = params;
  if (!postcode) {
    if (import.meta.env.DEV) {
      console.log("undefined postcode");
    }
    return null;
  }

  const url = new URL(request.url);
  const urlParams = new URLSearchParams(url.search);
  const { count } = Object.fromEntries(urlParams.entries());
  const numEntries = isNaN(Number(count)) ? 20 : Number(count);

  const urlPath = "/search/" + postcode + "?count=" + (numEntries + 20);
  console.log("urlPath", urlPath);
  return redirect(urlPath);
}
