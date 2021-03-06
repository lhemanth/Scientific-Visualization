// generated by Fast Light User Interface Designer (fluid) version 1.0304

#include "gui.h"

void Gui::cb_readFile_i(Fl_Menu_*, void*) {
  app->ReadFile();
}
void Gui::cb_readFile(Fl_Menu_* o, void* v) {
  ((Gui*)(o->parent()->user_data()))->cb_readFile_i(o,v);
}

void Gui::cb_writeFile_i(Fl_Menu_*, void*) {
  app->WriteFile();
}
void Gui::cb_writeFile(Fl_Menu_* o, void* v) {
  ((Gui*)(o->parent()->user_data()))->cb_writeFile_i(o,v);
}

void Gui::cb_exitButton_i(Fl_Menu_*, void*) {
  exit(1);
}
void Gui::cb_exitButton(Fl_Menu_* o, void* v) {
  ((Gui*)(o->parent()->user_data()))->cb_exitButton_i(o,v);
}

void Gui::cb_updateImage_i(Fl_Menu_*, void*) {
  app->updateImage();
}
void Gui::cb_updateImage(Fl_Menu_* o, void* v) {
  ((Gui*)(o->parent()->user_data()))->cb_updateImage_i(o,v);
}

void Gui::cb_averageSmoothing_i(Fl_Menu_*, void*) {
  app->averageSmoothing();
}
void Gui::cb_averageSmoothing(Fl_Menu_* o, void* v) {
  ((Gui*)(o->parent()->user_data()))->cb_averageSmoothing_i(o,v);
}

void Gui::cb_medianSmoothing_i(Fl_Menu_*, void*) {
  app->medianSmoothing();
}
void Gui::cb_medianSmoothing(Fl_Menu_* o, void* v) {
  ((Gui*)(o->parent()->user_data()))->cb_medianSmoothing_i(o,v);
}

void Gui::cb_gaussianSmooth_i(Fl_Menu_*, void*) {
  app->gaussianSmooth();
}
void Gui::cb_gaussianSmooth(Fl_Menu_* o, void* v) {
  ((Gui*)(o->parent()->user_data()))->cb_gaussianSmooth_i(o,v);
}

void Gui::cb_edgeDetection_i(Fl_Menu_*, void*) {
  app->edgeDetection();
}
void Gui::cb_edgeDetection(Fl_Menu_* o, void* v) {
  ((Gui*)(o->parent()->user_data()))->cb_edgeDetection_i(o,v);
}

void Gui::cb_undo_i(Fl_Menu_*, void*) {
  app->undo();
}
void Gui::cb_undo(Fl_Menu_* o, void* v) {
  ((Gui*)(o->parent()->user_data()))->cb_undo_i(o,v);
}

void Gui::cb_readVolumeFile_i(Fl_Menu_*, void*) {
  app->readVolumeFile();
}
void Gui::cb_readVolumeFile(Fl_Menu_* o, void* v) {
  ((Gui*)(o->parent()->user_data()))->cb_readVolumeFile_i(o,v);
}

void Gui::cb_X_i(Fl_Menu_*, void*) {
  app->xRay();
}
void Gui::cb_X(Fl_Menu_* o, void* v) {
  ((Gui*)(o->parent()->user_data()))->cb_X_i(o,v);
}

void Gui::cb_MIP_i(Fl_Menu_*, void*) {
  app->mip();
}
void Gui::cb_MIP(Fl_Menu_* o, void* v) {
  ((Gui*)(o->parent()->user_data()))->cb_MIP_i(o,v);
}

Fl_Menu_Item Gui::menu_menuBar[] = {
 {"File", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Read", 0,  (Fl_Callback*)Gui::cb_readFile, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Write", 0,  (Fl_Callback*)Gui::cb_writeFile, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Exit", 0,  (Fl_Callback*)Gui::cb_exitButton, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 1},
 {"Image Processing", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Update", 0,  (Fl_Callback*)Gui::cb_updateImage, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Average Smooth", 0,  (Fl_Callback*)Gui::cb_averageSmoothing, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Median Smooth", 0,  (Fl_Callback*)Gui::cb_medianSmoothing, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Gaussian Smooth", 0,  (Fl_Callback*)Gui::cb_gaussianSmooth, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Edge Detection", 0,  (Fl_Callback*)Gui::cb_edgeDetection, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Undo", 0,  (Fl_Callback*)Gui::cb_undo, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Volume Rendering", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Read Volume File", 0,  (Fl_Callback*)Gui::cb_readVolumeFile, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"X-Ray", 0,  (Fl_Callback*)Gui::cb_X, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"MIP", 0,  (Fl_Callback*)Gui::cb_MIP, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};
Fl_Menu_Item* Gui::fileMenu = Gui::menu_menuBar + 0;
Fl_Menu_Item* Gui::readFile = Gui::menu_menuBar + 1;
Fl_Menu_Item* Gui::writeFile = Gui::menu_menuBar + 2;
Fl_Menu_Item* Gui::exitButton = Gui::menu_menuBar + 4;
Fl_Menu_Item* Gui::imageProcessing = Gui::menu_menuBar + 5;
Fl_Menu_Item* Gui::updateImage = Gui::menu_menuBar + 6;
Fl_Menu_Item* Gui::averageSmoothing = Gui::menu_menuBar + 7;
Fl_Menu_Item* Gui::medianSmoothing = Gui::menu_menuBar + 8;
Fl_Menu_Item* Gui::gaussianSmooth = Gui::menu_menuBar + 9;
Fl_Menu_Item* Gui::edgeDetection = Gui::menu_menuBar + 10;
Fl_Menu_Item* Gui::undo = Gui::menu_menuBar + 11;
Fl_Menu_Item* Gui::volumeRendering = Gui::menu_menuBar + 13;
Fl_Menu_Item* Gui::readVolumeFile = Gui::menu_menuBar + 14;
Fl_Menu_Item* Gui::MIP = Gui::menu_menuBar + 16;

Gui::Gui() {
  { MainWindow = new Fl_Double_Window(985, 555, "Scientific Visualization Projects");
    MainWindow->user_data((void*)(this));
    { menuBar = new Fl_Menu_Bar(0, 0, 985, 25, "menuBar");
      menuBar->menu(menu_menuBar);
    } // Fl_Menu_Bar* menuBar
    { EditorWindow = new CEditorWindow(15, 25, 385, 350, "EditorWindow");
      EditorWindow->box(FL_NO_BOX);
      EditorWindow->color(FL_BACKGROUND_COLOR);
      EditorWindow->selection_color(FL_BACKGROUND_COLOR);
      EditorWindow->labeltype(FL_NORMAL_LABEL);
      EditorWindow->labelfont(0);
      EditorWindow->labelsize(14);
      EditorWindow->labelcolor(FL_FOREGROUND_COLOR);
      EditorWindow->align(Fl_Align(FL_ALIGN_CENTER));
      EditorWindow->when(FL_WHEN_RELEASE);
    } // CEditorWindow* EditorWindow
    { DisplayWindow = new CDisplayWindow(415, 25, 570, 530, "DisplayWindow");
      DisplayWindow->box(FL_NO_BOX);
      DisplayWindow->color(FL_BACKGROUND_COLOR);
      DisplayWindow->selection_color(FL_BACKGROUND_COLOR);
      DisplayWindow->labeltype(FL_NORMAL_LABEL);
      DisplayWindow->labelfont(0);
      DisplayWindow->labelsize(14);
      DisplayWindow->labelcolor(FL_FOREGROUND_COLOR);
      DisplayWindow->align(Fl_Align(FL_ALIGN_CENTER));
      DisplayWindow->when(FL_WHEN_RELEASE);
    } // CDisplayWindow* DisplayWindow
    MainWindow->end();
  } // Fl_Double_Window* MainWindow
  app=new Application();
}

void Gui::show() {
  MainWindow->show();
  EditorWindow->show();
  DisplayWindow->show();
}
