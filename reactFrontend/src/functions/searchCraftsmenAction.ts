import { redirect } from "react-router-dom";

export async function searchCraftsmenAction({
  request,
}: {
  request: Request;
}) {
  const formData = await request.formData();
  const updates = Object.fromEntries(formData);
  const { craftsmanId } = updates;
  // craftsmanId should be numeric, if not, redirect to search page
  if (
    typeof craftsmanId.valueOf() !== "string" ||
    isNaN(Number(craftsmanId.valueOf()))
  ) {
    if (import.meta.env.DEV) {
      console.log("craftsmanId is not valid", craftsmanId);
    }
    return redirect("/update");
  }
  // craftsmanId is valid, redirect to update page
  return redirect(`/update/${craftsmanId}`);
}
