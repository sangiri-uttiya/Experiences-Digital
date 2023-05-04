#include <pgmspace.h>

#define SECRET
#define THINGNAME "ESP32_LIGHT" // change this

const char AWS_IOT_ENDPOINT[] = "a1ujz06l179gqq-ats.iot.ap-south-1.amazonaws.com"; // change this

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAJD8DuK+tU97fyhQUiSRsejJxLtVMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMzA1MDMyMjU0
MTFaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCr3iW1qneyWfbArGit
7D7SHS6rIOcKEsAlQsiGpdEJPozIIUzGA7CZOYD0cuCu95rW0/J+XjFYcSh1/uu+
QRv+y9qW4RU0w2uMr8NmTfBDia8qxf/gy4j5RA5nmjKunJvJj8V24h9DlywcWuPw
Omd24jca9mlORLQ0e/cM+tOiQVknhCscFH9RgS2okonowGO6m4xCsvXXcdI6f9eN
Z+yJ6FHPftZ6/T1gdqOX81faPtv5wQQNcY7g1kpXpA59SdC95VB4KfpmS+VReWiq
11c4BYYjvLeFSKr4+/Gw3ae5Sn+wr4XsfGsj3pSZL6CIC02jVjfLWYVayWR6XVfo
2mG7AgMBAAGjYDBeMB8GA1UdIwQYMBaAFLvCOHXhkPiIaaXZ6NgA9b2QuUJQMB0G
A1UdDgQWBBTFHto0Lp6cyN8AWYcKyqILgH6SEDAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAevN7wcbL3zhccKcWlwPL/2jW
pgdIdwdGS1I9eIvk5LUjr0bCXd0LRtjujGt5l/PRZSR/VxmIZMnqr67YW2h1hq3Z
gZlp6rGGWuz19R8EUUTzn+RLaOD4ZxmFddzjlcoEpQXrdgGX9UyQ5n3BBgs5qKo/
kQxSMzkE3OD/XSRAi0jy8WgSxn5Ta+6my4ApQTq8hWih/c/l/Lk2BNV2GuGKxSzW
1sKBwNMbSj4y7L/yLp9RsvJPnC3h5uaULdG/Sx8bmIT11rsbBtIhsv+we4EW7Dx3
GNjmIVs05Iwuj+kUITa1PwVB7gzIq0T3cQGiVDevT7rdq2dVZr6IdXhL1/b6Zg==
-----END CERTIFICATE-----

 
 
)KEY";

// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEAq94ltap3sln2wKxorew+0h0uqyDnChLAJULIhqXRCT6MyCFM
xgOwmTmA9HLgrvea1tPyfl4xWHEodf7rvkEb/svaluEVNMNrjK/DZk3wQ4mvKsX/
4MuI+UQOZ5oyrpybyY/FduIfQ5csHFrj8DpnduI3GvZpTkS0NHv3DPrTokFZJ4Qr
HBR/UYEtqJKJ6MBjupuMQrL113HSOn/XjWfsiehRz37Wev09YHajl/NX2j7b+cEE
DXGO4NZKV6QOfUnQveVQeCn6ZkvlUXloqtdXOAWGI7y3hUiq+PvxsN2nuUp/sK+F
7HxrI96UmS+giAtNo1Y3y1mFWslkel1X6NphuwIDAQABAoIBAQCOtsTxeUAzpWi0
zXWPFqGDsB/UklnHj5JmXnJM/Nv7pSkZ9izeMKowUgO2+L2CDLFSumSecnDfU/eZ
I7l2HnK0vWoh533Ido2UIU9MYGOmcWo3RnsXm2t+MPkVJoH3ZKwoT25VLadwZNOI
KCEmlhjcKzQ++2auS3aoLlgTOyUJkYWWkdChmZZAruYsm7+JsFttEryEJT/GO1ij
4CanhfaNjrbhHvERBlMGcbdTDXNgYPa8pFZlgdjqIqyjvKIR9+VvyAbnAwG2T7WO
yK94qClN+7mlSUOXArNWWL84c5sfKEbNCvlFkMuZuB2dzhG/hiRZjSwn/0uKP4Kw
jdPkkFGBAoGBANa8GBVCU/Z5gTQqzuF8V7v605w6SZzUsydSJRDL6ockLkM/xoA/
9ScG6NhW1pFwpUPS+GuEifKQ4jHRlx46w/hgWx6lz9sFFTRUkadPi8xxO64ZeYb2
ORM92g2O9vVniawqixQ7qa/tNLY/eaKPb0jB/oTTKMbBuk5sNYl/CYSxAoGBAMzl
NMStsSSsGGdmwueQtOBJTSuq/193nnCnsm5bXoIdIFeIcsL0AHKRAMFQyHJGWthY
ohUvqAlkbYtBiIR8IUrAymJfgVoQA2XcOqaTA0buuzTR7j9UHdNpj93q1JjUIuh1
7tMe3y6ytDiHh+S7BfA4loneVsZrGCuP+Adg+JgrAoGAMwnoC32FaWr928FlBNFC
JSr8CwELqBwiLPFoX/Kn3tEpsdBBxQ/unAUXaPxS6aTFkzZc12lcRGxNZxvy+Dtt
guacIc+1dNBjdtm2+PZ+OuybC8mASiTR8hHcdyaI6lFetq4x+nAn5+nQgpTZu1qu
T7PUZAuwgHVha+xqWTD5uTECgYBSw+951xOsVZwSAK+QbKKzyshScGNxw9cLeKIZ
8+yMMInE8ggxefDIVoxwilo91u+RXtQyLKr7CEc7rkAgDChCkvftntiYccl9luVW
LiJvv7V9U6Oijy7xHD4SDW7NQTvMnP7Y5yqOKX+lKhIZsfZnH+SnUlnJEq+TwTcW
e/RPOwKBgGq5vhLUs80eYQMw72zZwr+9FtuKAFbTn6jHWg3uz+7iuz9S1miYuoM2
nqrZueqlNo49q3NrdpgETvHvqWWBUeVwTaJwR3kJSvtarOS3O15kcpHyeGppCkQn
Gv7fCNm7uX6QcyNlyVPgwjAgpXbNmOGD0BxGR++nhF/WSZs+a3Pa
-----END RSA PRIVATE KEY-----

 
 
)KEY";