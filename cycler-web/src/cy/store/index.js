import { createStore } from 'redux';
import reducer from '../reducer';

import enhancer from './enhancer';


export function configStore(initialState) {
  return enhancer(createStore)(
    reducer,
    initialState,
  );
}
