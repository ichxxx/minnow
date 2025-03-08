#include "byte_stream.hh"
using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) {}

void Writer::push( string data )
{
  if ( is_closed() ) return;

  uint64_t push_size = min( data.size(), available_capacity() );
  if ( push_size == 0 ) return;

  data.resize(push_size);
  buffer_queue_.emplace_back(move(data));

  size_ += push_size;
  write_bytes_ += push_size;
}

void Writer::close()
{
  closed_ = true;
}

bool Writer::is_closed() const
{
  return closed_;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - size_;
}

uint64_t Writer::bytes_pushed() const
{
  return write_bytes_;
}

string_view Reader::peek() const
{
  if ( buffer_queue_.empty() ) return "";
  return buffer_queue_.front();
}

void Reader::pop( uint64_t len )
{
  if ( bytes_buffered() == 0 ) return;

  uint64_t pop_size = 0;
  while ( len > 0 && buffer_queue_.size() > 0 )
  {
    auto& data = buffer_queue_.front();
  
    if ( len < data.size() )
    {
      data.erase(0, len);
      pop_size += len;
      break;
    }
  
    len -= data.size();
    pop_size += data.size();
    buffer_queue_.pop_front();
  }

  size_ -= pop_size;
  read_bytes_ += pop_size;
}

bool Reader::is_finished() const
{
  return ByteStream::writer().is_closed() && bytes_buffered() == 0;
}

uint64_t Reader::bytes_buffered() const
{
  return size_;
}

uint64_t Reader::bytes_popped() const
{
  return read_bytes_;
}

