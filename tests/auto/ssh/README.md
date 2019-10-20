ssh/sftp auto test
==================

This example needs or uses the following environment variables to know where
and how to connect to run the tests. I've just tested with an openssh server,
but in theory any should work.

 * `QTC_SSH_TEST_HOST`: The hostname of the server to connect to.
 * `QTC_SSH_TEST_PORT`: The port to connect to.
 * `QTC_SSH_TEST_USER`: The username to use when connecting.
 * `QTC_SSH_TEST_PASSWORD`: The password to use when connecting.
 * `QTC_SSH_TEST_KEYFILE`: The key file to use when connecting.
 * `QTC_SSH_TEST_KEYFILE`: The key file to use when connecting.

For the tunnel tests (uses `localhost` instead of `QTC_SSH_TEST_HOST`):
 * `QTC_SSH_TEST_PORT_TUNNEL`
 * `QTC_SSH_TEST_USER_TUNNEL`
 * `QTC_SSH_TEST_PASSWORD_TUNNEL`
 * `QTC_SSH_TEST_KEYFILE_TUNNEL`
