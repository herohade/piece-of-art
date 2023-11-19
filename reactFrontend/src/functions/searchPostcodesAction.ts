import { redirect } from "react-router-dom";

export async function searchPostcodesAction({
  request,
}: {
  request: Request;
}) {
  const formData = await request.formData();
  const updates = Object.fromEntries(formData);
  const { postcode } = updates;
  // postcode should be 5 digits, if not, redirect to search page
  if (
    typeof postcode.valueOf() !== "string" ||
    (postcode.valueOf() as string).length !== 5 ||
    isNaN(Number(postcode.valueOf())) ||
    Number(postcode.valueOf()) < 0
  ) {
    if (import.meta.env.DEV) {
      console.log("postcode is not valid", postcode);
    }
    return redirect("/search");
  }
  // postcode is valid, redirect to ranked results page
  return redirect(`/search/${postcode}`);
}
