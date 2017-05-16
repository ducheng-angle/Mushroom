/**
 *    > Author:            UncP
 *    > Mail:         770778010@qq.com
 *    > Github:    https://www.github.com/UncP/Mushroom
 *    > Created Time:  2017-04-22 21:19:57
**/

#ifndef _RAFT_SERVER_HPP_
#define _RAFT_SERVER_HPP_

#include <vector>

#include "../include/utility.hpp"
#include "../include/mutex.hpp"
#include "../include/cond.hpp"
#include "../rpc/rpc_server.hpp"

namespace Mushroom {

class Log;
class Thread;
class RpcConnection;
class RequestVoteArgs;
class RequestVoteReply;
class AppendEntryArgs;
class AppendEntryReply;
template<typename T> class BoundedQueue;

class RaftServer : public RpcServer
{
	public:
		enum State { Follower = 0x0, Candidate, Leader };

		static uint32_t ElectionTimeout;
		static uint32_t HeartbeatInterval;

		RaftServer(int32_t id, const std::vector<RpcConnection *> &peers);

		~RaftServer();

		void Vote(const RequestVoteArgs *args, RequestVoteReply *reply);

		void AppendEntry(const AppendEntryArgs *args, AppendEntryReply *reply);

		void Close();

		void Print() const;

	private:
		using RpcServer::Register;

		void Run();

		void Election();

		void RequestVote();

		bool SendAppendEntry();

		void BecomeFollower();

		void BecomeCandidate();

		using RpcServer::event_base_;

		int32_t  id_;

		uint8_t state_;
		bool    running_;
		bool    in_election_;
		bool    election_time_out_;
		bool    reset_timer_;

		uint32_t term_;
		int32_t  vote_for_;
		int32_t  commit_;
		int32_t  applied_;

		std::vector<Log> logs_;

		Mutex    mutex_;

		std::vector<RpcConnection *> peers_;

		std::vector<int32_t> next_;
		std::vector<int32_t> match_;

		BoundedQueue<Task> *queue_;
};

} // namespace Mushroom

#endif /* _RAFT_SERVER_HPP_ */