/*
 *  Copyright (c) 2019 by flomesh.io
 *
 *  Unless prior written consent has been obtained from the copyright
 *  owner, the following shall not be allowed.
 *
 *  1. The distribution of any source codes, header files, make files,
 *     or libraries of the software.
 *
 *  2. Disclosure of any source codes pertaining to the software to any
 *     additional parties.
 *
 *  3. Alteration or removal of any notices in or on the software or
 *     within the documentation included within the software.
 *
 *  ALL SOURCE CODE AS WELL AS ALL DOCUMENTATION INCLUDED WITH THIS
 *  SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION, WITHOUT WARRANTY OF ANY
 *  KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 *  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 *  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 *  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef WORKER_THREAD_HPP
#define WORKER_THREAD_HPP

#define ASIO_STANDALONE
#include <asio.hpp>

#include <thread>
#include <condition_variable>
#include <mutex>

namespace pipy {

class WorkerThread {
public:
  WorkerThread(int index);

  auto index() const -> int { return m_index; }

  bool start();
  void reload();
  auto stop(bool force = false) -> int;

private:
  int m_index;
  asio::io_context* m_io_context = nullptr;
  std::thread m_thread;
  std::mutex m_mutex;
  std::condition_variable m_cv;
  int m_pending_pipelines = 0;
  bool m_started = false;
  bool m_failed = false;
  bool m_shutdown = false;

  void fail();
};

} // namespace pipy

#endif // WORKER_THREAD_HPP