// brcdoc.cpp : implementation of the CMainDoc class
//
// Partially adopted the MFC's DIBAPI

#include <limits.h>
#include <all_tina.h>

#include "stdafx.h"
#include "selsim.h"
#include "mainfrm.h"
#include "saveim.h"
#include "simdialog.h"
#include "maindoc.h"
#include "myfile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainDoc

IMPLEMENT_DYNCREATE(CMainDoc, CDocument)

BEGIN_MESSAGE_MAP(CMainDoc, CDocument)
//{{AFX_MSG_MAP(CMainDoc)
	ON_COMMAND(ID_SIMULATOR_NEXTIMAGE, OnNext)
	ON_COMMAND(ID_SIMULATOR_OPENFILE, OnSimulatorOpenfile)
	ON_COMMAND(ID_PROCESS_CANNY, OnProcessCanny)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainDoc construction/destruction

CMainDoc::CMainDoc()
{
	m_file.m_hFile		= CFile::hFileNull;
	m_outFile.m_hFile	= CFile::hFileNull;

	m_pSimDlg			= NULL;
}



CMainDoc::~CMainDoc()
{
	if (m_file.m_hFile != CFile::hFileNull) // if open ...
	{
		m_file.Close();
	}
	if (m_outFile.m_hFile != CFile::hFileNull) // if open ...
	{
		m_outFile.Close();
	}

}

BOOL CMainDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
		return FALSE;
	
    return TRUE;
}



//
// Open an new document,
//
// TODO: Sort this routine out its a bit of a mess
//
//

BOOL CMainDoc::OnOpenDocument(const char* pszPathName)
{
	Imrect* pIm = NULL;
	HDIB hDIB = NULL;
    char* ext = strrchr(pszPathName, '.');	// get file extension (string after last dot)
	ext++;

	if ( (strnicmp(ext, "dib", 3) == 0) || 
		 (strnicmp(ext, "bmp", 3) == 0)) {
		
		// call DIB to Imrect routine
		pIm = DIB_read_image(pszPathName);

		if (pIm == NULL) { 
			// 
			// Try dlr bitmap  bitmap, use alternative reader
			if (m_file.m_hFile == CFile::hFileNull)	{ // if closed...
				if (!m_file.Open(pszPathName
								, CFile::modeRead | CFile::shareDenyWrite, &m_fe)) {
					return NULL;
				}
			}
			else {
				m_file.Close();
				if (!m_file.Open(pszPathName
								, CFile::modeRead | CFile::shareDenyWrite, &m_fe)) {
					return NULL;
				}
			}

			pIm = m_file.next();
			// only want to read one image 
			// Hence, close the file.
			if (m_file.m_hFile != CFile::hFileNull)	// if open ...
				m_file.Close();
		}
	}
	else  if ( strnicmp(ext, "aiff", 3) == 0 )
		// call Tina read image function 
		pIm = aiff_read_image((const char*)pszPathName); 
	else if ( strnicmp(ext, "bin", 3) == 0 ) {
		// not yet implemented
	}
	else if ( strnicmp(ext, "sel", 3) == 0)	{
		// Concatinated sel bitmap, use alternative reader
		if (m_file.m_hFile == CFile::hFileNull) // if closed ... 
		{
			if (!m_file.Open(pszPathName
							, CFile::modeRead | CFile::shareDenyWrite, &m_fe)) {
				return NULL;
			}
		}
		else
		{
			m_file.Close();
			if (!m_file.Open(pszPathName
							, CFile::modeRead | CFile::shareDenyWrite, &m_fe)) {
				return NULL;
			}
		}

		pIm = m_file.next();
	}

	
	if ( pIm == NULL )
     	return NO_IMAGE;

	if(pIm->vtype != float_v )
	{
	  // convert to float	
	  Imrect *pIm_float;
	  
	  pIm_float = im_cast(pIm, float_v);
	  im_free( pIm );
	  pIm = pIm_float;	  
	}
			
	// convert Imrect structure into a DIB and return
	if ( !(hDIB = ImrectToDIB(pIm)) )
		return NO_DIB;

	// initialise the member variables
	ReplaceHDIB( hDIB );
	ReplacePIM( pIm);
		
	// initialise display object
	if (!InitDIBData())
		return NO_INITIALISATION;
      	
	display_image();

	return 	IMAGE_OK;
}

////
// Save file
//
BOOL  CMainDoc::OnSaveDocument(const char* pszPathName)
{
	BOOL    ret_code = FALSE;
    char* ext = strrchr(pszPathName, '.');	// get file extension (string after last dot)

	if ( strnicmp(ext, ".aif", 3) == 0 ) {
		// call Tina write image function 
		ret_code = aiff_write_image(GetImrect(), (const char*)pszPathName); 
	}
	else {
		////
		// save image in default DLR format
		//
		sprintf( ++ext, "bmp" ); // replace extension with bmp

		if ( m_outFile.m_hFile != CFile::hFileNull ) {// if open - close it
			m_outFile.Close();
		}

		TRY	{
				m_outFile.Open( pszPathName
					, CFile::modeCreate | CFile::modeWrite  );
			}
		CATCH( CFileException, e ) {
#ifdef _DEBUG
				afxDump << "File could not be opened " << e->m_cause << "\n";
#endif
			return ret_code;
		}
		END_CATCH

		// save the image in default format
		SaveImageToFile();

		m_outFile.Close();
	}
	return ret_code;
}

////
// step forward and backwards through the image
//

void CMainDoc::OnNext()
{
	ReplacePIM( m_file.next() );	// Replace edge image inside document
	display_image();
}

void CMainDoc::Rewind(unsigned int imageno) 
{
	CString strStatus;
	strStatus.Format( "Image number %d", imageno); 

	theApp.m_pMframe->ModifyStatusBar(strStatus.GetBuffer(1)
		, 0
		, strStatus.GetBuffer(1));
	

	//
	// rewind input file and display the image we have rewound to.
	//
	ReplacePIM( m_file.previous() );	// Replace image inside document
	display_image();

	//
	// rewind the  output files
	//
	m_outFile.previous();
}

//
// Open output file
// Was image validation is now simulation
//
//
void CMainDoc::OnSimulatorOpenfile() 
{
 static CFileDialog 
	 x( TRUE
	 ,	NULL
	 ,	NULL
	 ,	OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
	 , "Fil files (*.fil)|*.fil|\
	BMP files (*.bmp,*.dib)|*.bmp;*.dib|\
	Bin files (*.bin)|*.bin|\
	AIF files (*.aiff)|*.aiff|\
	All files (*.*)|*.*||"
	 );
	 const int nMaxFile = 1024;
	 CString Filenames( '\0',nMaxFile);

	//x.m_ofn.Flags |=  OFN_ALLOWMULTISELECT;
	x.m_ofn.lpstrFile = Filenames.GetBuffer(nMaxFile);
	x.m_ofn.nMaxFile  = nMaxFile;
    if (x.DoModal()==IDOK) {

		CString filename = x.GetPathName();

		if ( m_outFile.m_hFile != CFile::hFileNull ) // if open ...
		{
			m_outFile.Close();
		}

		TRY	{
				m_outFile.Open( filename
					, CFile::modeCreate | CFile::modeReadWrite );
			}
		CATCH( CFileException, e ) {
#ifdef _DEBUG
				afxDump << "File could not be opened " << e->m_cause << "\n";
#endif
			return;
		}
		END_CATCH
			
		// start image simulation dialog
		if (m_pSimDlg == NULL) {
			//
			// Create a modeless dialog, for contol of image shifting
			// 
			m_pSimDlg = new CSimDialog(this, theApp.m_pMframe);
			
			if (m_pSimDlg->Create() != TRUE)
				TRACE( "Error creating dialog" );
			
			m_pSimDlg->ShowWindow(SW_SHOWNORMAL);
		}
	}
}

////
// modeless dialog call backs
//
void CMainDoc::BoxDone()
{
	//
	// this function is called by the modeless dialog as it terminates
	// just reset our pushbutton to be enabled again.
	// I _don't_ delete the MFC CDialog object because the dialog's own
	// code will do that.
	//
	m_pSimDlg = NULL;

	// don't delete m_pModeless; !
	theApp.m_pMframe->EnableWindow();

	// close the output file associated with the modeless dialog.
	TRY	{
		m_outFile.Close();
	}
	CATCH( CFileException, e ) {
#ifdef _DEBUG
		afxDump << "File could not be closed " << e->m_cause << "\n";
#endif
		return;
	}
	END_CATCH

	//
	// close associated documents
	//
	while(m_docs.size() > 0) {
		CSimDocVec::iterator pDoc = m_docs.end() - 1;
		// close the document down
		(*pDoc)->OnCloseDocument();

		// delete the last item in the vector
		m_docs.pop_back();
	}

}

void CMainDoc::Skip() 
{
	// if the image is not ok simply skip onto the next image
	OnNext();
}

////
// Save output file
//
//
bool  CMainDoc::SaveImageToFile(Imrect *pIm)
{
	short    *ivector = Imrect2svec(pIm); // represent current image as a vector
	bool     ret_code = false;

	if (ivector != NULL) {
		ret_code = (bool)(::SaveImageToFile((short *) ivector
			, &m_outFile
			, pIm->width
			, pIm->height
			, BMPFILES));

		delete ivector;
	}

	return ret_code;
}


bool  CMainDoc::SaveImageToFile()
{
	return SaveImageToFile(GetImrect());
}

////
// Main simulation routine called from the SimDialog 
// dialog
//

void CMainDoc::DoSimulation(unsigned int imageno) 
{
	// moves in next raw image
	OnNext();
	if (m_file.m_hFile == CFile::hFileNull)	 // input file closed
											 // doesn't look like there is a next
		return; 

	// update status bar
	CString strStatus;
	strStatus.Format( "Image number %d", imageno); 
	theApp.m_pMframe->ModifyStatusBar(strStatus.GetBuffer(1)
		, 0
		, strStatus.GetBuffer(1));
	

	///
	// If there aren't enough views to display the results
	// tell the application to create some more, via the associated 
	// documents. 
	//
	// Currently, 
	// two associated documents are created, one to contain the
	// filtered image and one for the diff buffers
	//
	if (m_docs.size() < num_doc_indices) {
		CDocTemplate *pDocTemplate = theApp.GetDocTemplate(IDR_SIMTYPE);
		//
		// Size too small, add some extra views
		//
		if (pDocTemplate != NULL) {
			for (Doc_idx idx = (Doc_idx)m_docs.size(); idx < num_doc_indices; idx++) {
				AddAssocDoc((CSimDoc *) pDocTemplate->OpenDocumentFile(NULL, FALSE));
			} 
		} else {
			MessageBox(NULL
			, "Failed to obtain document template can't create simulator views"
			, NULL
			, MB_ICONINFORMATION | MB_OK);
		}

	}

	// do the simulation
	if ( theSimulator(GetImrect()) ) {
		// update filter document
		Imrect *pIm   = theSimulator.get_image(CSimInterface::filtered_image_idx);
		CSimDocVec::iterator pDoc = m_docs.begin();
		// deal with filtered image
		(*pDoc)->ReplacePIM( pIm );
		(*pDoc)->display_image();
		SaveImageToFile( pIm );
	}
}

void CMainDoc::OnProcessCanny() 
{
  	   // result edge image

	// Calculate edge rect 
    BeginWaitCursor();
	Imrect   *rEIm   = (Imrect *) canny( GetImrect()
						, 1.2 // sigma
						, 0.01 // precision
						, 3.0 // lowThre
						, 5.0 // upThre
						, 3.0 // lenThre 
					  );
	
	List *strings = (List *) prop_get(rEIm->props, STRING);
  	
	strings = linear_strings(strings, 3.0);
    strings = geom_list_make_flat(strings);

	// update the contents of the document
    ReplacePGeom( strings ); // equivalent to mono_geom_set(strings);
	ReplacePEIM( rEIm );     // Replace edge image inside document

	EndWaitCursor();
}

/////////////////////////////////////////////////////////////////////////////
// CMainDoc diagnostics

#ifdef _DEBUG
void CMainDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMainDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif

