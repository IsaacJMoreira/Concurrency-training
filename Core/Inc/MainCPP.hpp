/*
 * MainCPP.hpp
 *
 *  Created on: Jun 19, 2024
 *      Author: isaac
 */

#ifndef INC_MAINCPP_HPP_
#define INC_MAINCPP_HPP_

void MainCPP();

#ifdef __cplusplus
extern "C"
{
#endif
	void MainC();
	void RotaryEncoderWrapper();
	void ButtonEncoderWrapper();
#ifdef __cplusplus
}
#endif

#endif /* INC_MAINCPP_HPP_ */
