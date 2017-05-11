import { createAction } from 'redux-actions';

import { now, reset } from '../api';


export default {
  updateNow: createAction('UPDATE_NOW', now),
  reset: createAction('RESET', reset)
};
