import { handleActions } from 'redux-actions';
import actionCreators from '../action/creators';

const initialState = {
  now: {}
};

export default handleActions({
  [actionCreators.updateNow](state, { payload: now }) {
    if (now) {
      return {
        now
      };
    }
    return initialState;
  },
  [actionCreators.reset]() {
    return initialState;
  }
}, initialState);
