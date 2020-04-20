#include "restclient-cpp/connection.h"
#include "restclient-cpp/restclient.h"

// initialize RestClient
RestClient::init();

// get a connection object
RestClient::Connection* conn = new RestClient::Connection("http://url.com");

// configure basic auth
conn->SetBasicAuth("WarMachine68", "WARMACHINEROX");

// set connection timeout to 5s
conn->SetTimeout(5);

// set custom user agent
// (this will result in the UA "foo/cool restclient-cpp/VERSION")
conn->SetUserAgent("foo/cool");

// enable following of redirects (default is off)
conn->FollowRedirects(true);
// and limit the number of redirects (default is -1, unlimited)
conn->FollowRedirects(true, 3);

// set headers
RestClient::HeaderFields headers;
headers["Accept"] = "application/json";
conn->SetHeaders(headers)


// append additional headers
conn->AppendHeader("X-MY-HEADER", "foo")

// if using a non-standard Certificate Authority (CA) trust file
conn->SetCAInfoFilePath("/etc/custom-ca.crt")

RestClient::Response r = conn->get("/get")
RestClient::Response r = conn->head("/get")
RestClient::Response r = conn->del("/delete")
RestClient::Response r = conn->options("/options")

// set different content header for POST, PUT and PATCH
conn->AppendHeader("Content-Type", "application/json")
RestClient::Response r = conn->post("/post", "{\"foo\": \"bla\"}")
RestClient::Response r = conn->put("/put", "application/json", "{\"foo\": \"bla\"}")
RestClient::Response r = conn->patch("/patch", "text/plain", "foobar")

// deinit RestClient. After calling this you have to call RestClient::init()
// again before you can use it
RestClient::disable();
The responses are again of type RestClient::Response and have three attributes:

RestClient::Response.code // HTTP response code
RestClient::Response.body // HTTP response body
RestClient::Response.headers // HTTP response headers
The connection object also provides a simple way to get some diagnostics and metrics information via conn->GetInfo(). The result is a RestClient::Connection::Info struct and looks like this:

typedef struct {
  std::string base_url;
  RestClients::HeaderFields headers;
  int timeout;
  struct {
    std::string username;
    std::string password;
  } basicAuth;

  std::string certPath;
  std::string certType;
  std::string keyPath;
  std::string keyPassword;
  std::string customUserAgent;
  std::string uriProxy;
  struct {
    // total time of the last request in seconds Total time of previous
    // transfer. See CURLINFO_TOTAL_TIME
    int totalTime;
    // time spent in DNS lookup in seconds Time from start until name
    // resolving completed. See CURLINFO_NAMELOOKUP_TIME
    int nameLookupTime;
    // time it took until Time from start until remote host or proxy
    // completed. See CURLINFO_CONNECT_TIME
    int connectTime;
    // Time from start until SSL/SSH handshake completed. See
    // CURLINFO_APPCONNECT_TIME
    int appConnectTime;
    // Time from start until just before the transfer begins. See
    // CURLINFO_PRETRANSFER_TIME
    int preTransferTime;
    // Time from start until just when the first byte is received. See
    // CURLINFO_STARTTRANSFER_TIME
    int startTransferTime;
    // Time taken for all redirect steps before the final transfer. See
    // CURLINFO_REDIRECT_TIME
    int redirectTime;
    // number of redirects followed. See CURLINFO_REDIRECT_COUNT
    int redirectCount;
  } lastRequest;
} Info;
