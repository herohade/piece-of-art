import { DefaultService, OpenAPI } from "../services/openapi";

const { getCraftsmen, patchCraftman } = DefaultService;

OpenAPI.BASE = "http://localhost:3000";

export const getCraftsmenByPostalCode = async (postalCode: string) => {
  try {
    return await getCraftsmen(postalCode);
  } catch (error) {
    console.error(error);
  }
};

export const patchCraftmanProfile = async (
  craftmanId: number,
  maxDrivingDistance: number | null,
  profilePictureScore: number | null,
  profileDescriptionScore: number | null
) => {
  return await patchCraftman(craftmanId, {
    maxDrivingDistance,
    profilePictureScore,
    profileDescriptionScore,
  });
};
