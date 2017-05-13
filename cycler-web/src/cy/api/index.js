import { get, post } from '../http/client';

const BASE_URL = 'http://192.168.2.222/api';

export async function now() {
  const data = await get(`${BASE_URL}/now?rnd=${Math.random()}`);
  return data;
}

export async function reset() {
  await post(`${BASE_URL}/reset`);
}
