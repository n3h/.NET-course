#include <windows.h>
#include "stdafx.h"
#include <ole2.h>
#include <iostream>

// 
// AutoWrap() - Automation helper function...
// 
HRESULT AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp,
	LPOLESTR ptName, int cArgs...)
{
	// Begin variable-argument list...
	va_list marker;
	va_start(marker, cArgs);

	if (!pDisp) {
		MessageBox(NULL, TEXT("NULL IDispatch passed to AutoWrap()"),
			TEXT("Error"), 0x10010);
		_exit(0);
	}

	// Variables used...
	DISPPARAMS dp = { NULL, NULL, 0, 0 };
	DISPID dispidNamed = DISPID_PROPERTYPUT;
	DISPID dispID;
	HRESULT hr;
	char buf[200];
	char szName[200];

	// Convert down to ANSI
	WideCharToMultiByte(CP_ACP, 0, ptName, -1, szName, 256, NULL, NULL);

	// Get DISPID for name passed...
	hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT,
		&dispID);
	if (FAILED(hr)) {
		sprintf(buf,
			"IDispatch::GetIDsOfNames(\"%s\") failed w/err0x%08lx",
			szName, hr);
		MessageBox(NULL, (LPCWSTR)buf, TEXT("AutoWrap()"), 0x10010);
		_exit(0);
		return hr;
	}

	// Allocate memory for arguments...
	VARIANT *pArgs = new VARIANT[cArgs + 1];

	// Extract arguments...
	for (int i = 0; i<cArgs; i++) {
		pArgs[i] = va_arg(marker, VARIANT);
	}

	// Build DISPPARAMS
	dp.cArgs = cArgs;
	dp.rgvarg = pArgs;

	// Handle special-case for property-puts!
	if (autoType & DISPATCH_PROPERTYPUT) {
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
	}

	// Make the call!
	hr = pDisp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, autoType,
		&dp, pvResult, NULL, NULL);
	if (FAILED(hr)) {
		sprintf(buf,
			"IDispatch::Invoke(\"%s\"=%08lx) failed w/err 0x%08lx",
			szName, dispID, hr);
		MessageBox(NULL, (LPCWSTR)buf, TEXT("AutoWrap()"), 0x10010);
		_exit(0);
		return hr;
	}
	// End variable-argument section...
	va_end(marker);

	delete[] pArgs;

	return hr;

}

int main(int argc, char* argv[])
{
	// Initialize COM for this thread...
	CoInitialize(NULL);

	// Get CLSID for Word.Application...
	CLSID clsid;
	HRESULT hr = CLSIDFromProgID(L"Word.Application", &clsid);
	if (FAILED(hr)) {
		::MessageBox(NULL, TEXT("CLSIDFromProgID() failed"), TEXT("Error"),
			0x10010);
		std::cout << "err1";
		return -1;
	}

	// Start and get IDispatch...
	IDispatch *pWordApp;

	hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER,
		IID_IDispatch, (void **)&pWordApp);
	if (FAILED(hr)) {
		::MessageBox(NULL, TEXT("Word not registered properly"),
			TEXT("Error"), 0x10010);
		std::cout << "err2";
		return -2;
	}

	// Make visible
	/*
	{
	VARIANT x;
	x.vt = VT_I4;
	x.lVal = 1;
	AutoWrap(DISPATCH_PROPERTYPUT, NULL, pWordApp, L"Visible", 1, x);
	}
	*/

	// Get Documents collection
	IDispatch *pDocs;
	{
		VARIANT result;
		VariantInit(&result);
		AutoWrap(DISPATCH_PROPERTYGET, &result, pWordApp, L"Documents", 0);

		pDocs = result.pdispVal;
	}

	// Stworz nowy dokument
	IDispatch *pActiveDocument;
	{
		VARIANT result;
		VariantInit(&result);

		AutoWrap(DISPATCH_METHOD, &result, pDocs, L"Add", 0);

		pActiveDocument = result.pdispVal;
	}

	// Dodaj tekst
	IDispatch *pParas = NULL;
	{
		VARIANT result;
		VariantInit(&result);
		AutoWrap(DISPATCH_PROPERTYGET, &result, pActiveDocument, L"Paragraphs", 0);
		pParas = result.pdispVal;
	}

	IDispatch *pPara = NULL;
	{
		VARIANT result;
		VariantInit(&result);
		AutoWrap(DISPATCH_METHOD, &result, pParas, L"Add", 0);
		pPara = result.pdispVal;
	}

	IDispatch *pParaRng = NULL;
	{
		VARIANT result;
		VariantInit(&result);
		AutoWrap(DISPATCH_PROPERTYGET, &result, pPara, L"Range", 0);
		pParaRng = result.pdispVal;
	}

	{
		VARIANT x;
		x.vt = VT_BSTR;
		x.bstrVal = ::SysAllocString(L"Programowanie pod Windows");
		AutoWrap(DISPATCH_PROPERTYPUT, NULL, pParaRng, L"Text", 1, x);
		VariantClear(&x);
	}

	// Zapisz
	{
		VARIANT vtFileName;
		vtFileName.vt = VT_BSTR;
		vtFileName.bstrVal = SysAllocString(L"D:\ppw.doc");
		AutoWrap(DISPATCH_METHOD, NULL, pActiveDocument, L"SaveAs", 1, vtFileName);
		VariantClear(&vtFileName);
	}

	// Close
	AutoWrap(DISPATCH_METHOD, NULL, pDocs, L"Close", 0);

	// Quit
	_putws(L"Quit");
	AutoWrap(DISPATCH_METHOD, NULL, pWordApp, L"Quit", 0);

	// Cleanup
	pParaRng->Release();
	pPara->Release();
	pActiveDocument->Release();
	pDocs->Release();
	pWordApp->Release();

	// Uninitialize COM for this thread...
	CoUninitialize();

	return 0;
}
