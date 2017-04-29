/**
 *    > Author:            UncP
 *    > Mail:         770778010@qq.com
 *    > Github:    https://www.github.com/UncP/Mushroom
 *    > Created Time:  2017-04-22 21:22:47
**/

#ifndef _RPC_HPP_
#define _RPC_HPP_

namespace Mushroom {

class RPC
{
	public:
		void Add();

		bool Call(const char *fun, const void *args, void *reply);
	private:
};

} // namespace Mushroom

#endif /* _RPC_HPP_ */