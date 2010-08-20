/* -*- mode: C++ -*-
 * 
 *  Navigator E-stop finite state machine states
 *
 *  Copyright (C) 2007, 2010, Austin Robot Technology
 *
 *  License: Modified BSD Software License Agreement
 *
 *  $Id$
 *
 *  Author: Jack O'Quin
 */


#ifndef __NAV_ESTOP_STATE_H__
#define __NAV_ESTOP_STATE_H__

#include <art_nav/EstopState.h>
#include <art_nav/FSMstate.h>

class NavEstopState: FSMstate
{
public:

  // navigator E-stop control states
  typedef enum
    {
      Done,				// mission finished (disabled)
      Pause,				// E-stop pause
      Run,				// E-stop run enabled
      N_states
    } state_t;

  NavEstopState()
  {
    this->state = Pause;
  }

  NavEstopState(state_t &istate)
  {
    this->state = istate;
  }

  NavEstopState(const art_nav::EstopState &estop_msg)
  {
    this->state = (NavEstopState::state_t) estop_msg.state;
  }

  ~NavEstopState();

  state_t Value(void) const
  {
    return this->state;
  }

  // return state name as a C string
  const char *Name(void) const
  {
    static const char *state_name[N_states] =
      {
	"Done",
	"Pause",
	"Run",
      };
    return state_name[this->state];
  }

  void operator=(const NavEstopState::state_t &newstate)
  {
    this->state = newstate;
  }

  void operator=(uint16_t value)
  {
    this->state = (NavEstopState::state_t) value;
  }

  bool operator==(const NavEstopState &compare) const
  {
    return this->state == compare.state;
  }

  bool operator==(const state_t &compare) const
  {
    return this->state == compare;
  }

  bool operator!=(const NavEstopState &compare) const
  {
    return this->state != compare.state;
  }

  bool operator!=(const state_t &compare) const
  {
    return this->state != compare;
  }

private:
  state_t state;
};

#endif // __NAV_ESTOP_STATE_H__
