/**********************************************************************
 *
 * This code is part of the MRcore project
 * Author:  Cristina Gajate & Miguel Hernando Gutierrez
 * 
 *
 * MRcore is licenced under the Common Creative License,
 * Attribution-NonCommercial-ShareAlike 3.0
 *
 * You are free:
 *   - to Share - to copy, distribute and transmit the work
 *   - to Remix - to adapt the work
 *
 * Under the following conditions:
 *   - Attribution. You must attribute the work in the manner specified
 *     by the author or licensor (but not in any way that suggests that
 *     they endorse you or your use of the work).
 *   - Noncommercial. You may not use this work for commercial purposes.
 *   - Share Alike. If you alter, transform, or build upon this work,
 *     you may distribute the resulting work only under the same or
 *     similar license to this one.
 *
 * Any of the above conditions can be waived if you get permission
 * from the copyright holder.  Nothing in this license impairs or
 * restricts the author's moral rights.
 *
 * It is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  
 **********************************************************************/

#include "euitibotsim.h"
#include <iostream>


namespace mr
{
IMPLEMENT_MR_OBJECT(EUITIbotSim)
void EUITIbotSim::writeToStream(Stream& stream)
 {SolidEntity::writeToStream(stream);}
void EUITIbotSim::readFromStream(Stream& stream)
 {SolidEntity::readFromStream(stream);}
void EUITIbotSim::writeToXML(XMLElement* parent)
{
	SolidEntity::writeToXML(parent);
}
void EUITIbotSim::readFromXML(XMLElement* parent)
{
	SolidEntity::readFromXML(parent);
}

char* EUITIbotSim::CreateXMLText()
{
	XMLElement* elem=new XMLElement(0,"EUITIbotSim");
	writeToXML(elem);
	return elem->CreateXMLText();
}

void EUITIbotSim::loadFromXMLText(char *XmlText)
{
	XML x;
	readFromXML(x.Paste(XmlText));
}

EUITIbotSim::EUITIbotSim()
{
	name="EUITIbot";
	//Units in meters and rad.

	for(int j=0;j<6;j++)q_init.push_back(0);


	vector<Vector2D> list;
	Actuator* actuator;

//Base = link[0]
	ComposedEntity *link=new ComposedEntity;
	link->setName("Base");

//**************************************//
// LA BASE ESTA FORMADA POR UN CILINDRO //
//**************************************//

			// CILINDRO(Cilindro)
			CylindricalPart *auxCyl=new CylindricalPart(0.5,0.425);//Altura y radio
			auxCyl->setColor(255,233,0);
			(*link)+=auxCyl;

			// A�ADIMOS AL VECTOR LINKS
			(*this)+=link;
			links.push_back(link);



////////////////////////////////////////////////////////////////////////////
//////////////////////////ARTICULACION 1 = LINK[1]//////////////////////////
////////////////////////////////////////////////////////////////////////////

			//JOINT[0] = ARTICULACION 1 ROTACIONAL
			SimpleJoint *auxJoint=new SimpleJoint(PI/2,-PI/2,true,0,Z_AXIS,false);
			auxJoint->setRelativePosition(Vector3D(0,0,0.52));
			auxJoint->LinkTo(links[0]);
			auxJoint->setValue(q_init[0]);
			joints.push_back(auxJoint);
			
			actuator=new Actuator();
			actuator->linkTo(auxJoint);
			actuators.push_back(actuator);

			//NUEVO GRUPO DE PIEZAS
			link=new ComposedEntity;
			link->setName("Link 1");


//***********************************************************************//
// LA ARTICULACION 1 ESTA COMPUESTA POR UN CILINDRO Y DOS PRISMAS IRREG. //
//***********************************************************************//
			// CILINDRO(Cilindro)
			auxCyl=new CylindricalPart(0.06,0.425);//Altura y radio
			auxCyl->setColor(255,0,0);
			(*link)+=auxCyl;

			// PRISMA IRREGULAR DERECHO(Pris_Der)
			PrismaticPart *auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.155,0));
			list.push_back(Vector2D(0.155,0));
			list.push_back(Vector2D(0.155,0.5));
			list.push_back(Vector2D(0.125,0.55));
			list.push_back(Vector2D(-0.125,0.55));
			list.push_back(Vector2D(-0.155,0.5));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(255,0,0);
			auxPrism->setHeight(0.1);
			auxPrism->setRelativePosition(Vector3D(-0.4,0,0.06));
			auxPrism->setRelativeOrientation(PI/2, 0, PI/2);
			
			(*link)+=auxPrism;

			// PRISMA IRREGULAR IZQUIERDO(Cil_Izq)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.155,0));
			list.push_back(Vector2D(0.155,0));
			list.push_back(Vector2D(0.155,0.5));
			list.push_back(Vector2D(0.125,0.55));
			list.push_back(Vector2D(-0.125,0.55));
			list.push_back(Vector2D(-0.155,0.5));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(255,0,0);
			auxPrism->setHeight(0.1);
			auxPrism->setRelativePosition(Vector3D(0.3,0,0.06));
			auxPrism->setRelativeOrientation(PI/2, 0 , PI/2);
			
			(*link)+=auxPrism;

			// SERVO2(Servo2)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.095,-0.2));
			list.push_back(Vector2D(0.095,-0.2));
			list.push_back(Vector2D(0.095,0.2));
			list.push_back(Vector2D(-0.095,0.2));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(0,0,0);
			auxPrism->setHeight(0.35);
			(*link)+=auxPrism;

			// SERVO3(Servo3)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.095,-0.2));
			list.push_back(Vector2D(0.095,-0.2));
			list.push_back(Vector2D(0.095,0.2));
			list.push_back(Vector2D(-0.095,0.2));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(0,0,0);
			auxPrism->setHeight(0.35);
			auxPrism->setRelativePosition(Vector3D(-0.29,0,0.3));
			auxPrism->setRelativeOrientation(Z_AXIS,-PI/2);
			(*link)+=auxPrism;

			// A�ADIMOS AL VECTOR LINKS
			link->LinkTo(joints[0]);
			links.push_back(link);

////////////////////////////////////////////////////////////////////////////
//////////////////////////ARTICULACION 2 = LINK[2]//////////////////////////
////////////////////////////////////////////////////////////////////////////

			//JOINT[1] = ARTICULACION 2 ROTACIONAL 
			auxJoint=new SimpleJoint(25*PI/36 , -25*PI/36,true,0,Z_AXIS,false);
			auxJoint->setRelativePosition(Vector3D(0.29,0,0.47));
			auxJoint->setRelativeOrientation(0,-PI/2,0);
			auxJoint->LinkTo(joints[0]);
			auxJoint->setValue(q_init[1]);
			joints.push_back(auxJoint);
			//	joints[1]->setDrawReferenceSystem(true);

	actuator=new Actuator();
	actuator->linkTo(auxJoint);
	actuators.push_back(actuator);

			//NUEVO GRUPO DE PIEZAS
			link=new ComposedEntity;
			link->setName("Link 2");

//***********************************************************************//
// LA ARTICULACION 2 ESTA COMPUESTA POR 4 CILINDROS Y 6 PRISMAS IRREG.   //
//***********************************************************************//

			// CILINDRO IZQUIERDO ABAJO(Cil_Ab_Izq)
			auxCyl=new CylindricalPart(0.03,0.175);//Altura y radio
			auxCyl->setColor(255,233,0);
			auxCyl->setRelativePosition(Vector3D(0,0,0));
			(*link)+=auxCyl;

			// PRISMA IRREGULAR IZQUIERDA(Pris_Izq)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.13,0));
			list.push_back(Vector2D(0.13,0));
			list.push_back(Vector2D(0.13,1.1));
			list.push_back(Vector2D(-0.13,1.1));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(255,233,0);
			auxPrism->setHeight(0.03);
			auxPrism->setRelativePosition(Vector3D(0,0,0));
			auxPrism->setRelativeOrientation(Z_AXIS,-PI/2);
			(*link)+=auxPrism;

			// CILINDRO IZQUIERDO ARRIBA(Cil_Ar_Izq)
			auxCyl=new CylindricalPart(0.03,0.175);//Altura y radio
			auxCyl->setColor(255,233,0);
			auxCyl->setRelativePosition(Vector3D(1.1,0,0));
			(*link)+=auxCyl;


			// PRISMA IRREGULAR REFUERZO IZQUIERDA(Pris_Ref_Izq)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.4,0));
			list.push_back(Vector2D(0.4,0));
			list.push_back(Vector2D(0.315,0.04));
			list.push_back(Vector2D(-0.315,0.04));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(255,233,0);
			auxPrism->setHeight(0.26);
			auxPrism->setRelativePosition(Vector3D(0.55,-0.13,0));
			auxPrism->setRelativeOrientation(X_AXIS,-PI/2);
			(*link)+=auxPrism;

			// PRISMA IRREGULAR CENTRO ABAJO(Pris_Cen_Ab)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(0,0));
			list.push_back(Vector2D(0.49,0));
			list.push_back(Vector2D(0.49,0.08));
			list.push_back(Vector2D(0.4,0.08));
			list.push_back(Vector2D(0.4,0.27));
			list.push_back(Vector2D(0.33,0.27));
			list.push_back(Vector2D(0.33,0.08));
			list.push_back(Vector2D(0.16,0.08));
			list.push_back(Vector2D(0.16,0.27));
			list.push_back(Vector2D(0.09,0.27));
			list.push_back(Vector2D(0.09,0.08));
			list.push_back(Vector2D(0,0.08));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(255,233,0);
			auxPrism->setHeight(0.2);
			auxPrism->setRelativePosition(Vector3D(0.38,-0.1,0.03));
			auxPrism->setRelativeOrientation(0,-PI/2,-PI/2);
			
			(*link)+=auxPrism;

			// PRISMA IRREGULAR CENTRO ARRIBA(Pris_Cen_Ar)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(0,0));
			list.push_back(Vector2D(0.49,0));
			list.push_back(Vector2D(0.49,0.08));
			list.push_back(Vector2D(0,0.08));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(255,233,0);
			auxPrism->setHeight(0.2);
			auxPrism->setRelativePosition(Vector3D(0.64,-0.1,0.03));
			auxPrism->setRelativeOrientation(0,-PI/2,-PI/2);

			(*link)+=auxPrism;

			// CILINDRO DERECHO ABAJO(Cil_Ab_Der)
			auxCyl=new CylindricalPart(0.03,0.175);//Altura y radio
			auxCyl->setColor(255,233,0);
			auxCyl->setRelativePosition(Vector3D(0,0,0.52));
			(*link)+=auxCyl;

			// PRISMA IRREGULAR DERECHA(Pris_Der)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.13,0));
			list.push_back(Vector2D(0.13,0));
			list.push_back(Vector2D(0.13,1.1));
			list.push_back(Vector2D(-0.13,1.1));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(255,233,0);
			auxPrism->setHeight(0.03);
			auxPrism->setRelativePosition(Vector3D(0,0,0.52));
			auxPrism->setRelativeOrientation(Z_AXIS,-PI/2);
			(*link)+=auxPrism;
			

			// CILINDRO DERECHO ARRIBA(Cil_Ar_Der)
			auxCyl=new CylindricalPart(0.03,0.175);//Altura y radio
			auxCyl->setColor(255,233,0);
			auxCyl->setRelativePosition(Vector3D(1.1,0,0.52));
			(*link)+=auxCyl;

			// PRISMA IRREGULAR REFUERZO DERECHA(Pris_Ref_Der)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.4,0));
			list.push_back(Vector2D(0.4,0));
			list.push_back(Vector2D(0.315,0.04));
			list.push_back(Vector2D(-0.315,0.04));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(255,233,0);
			auxPrism->setHeight(0.26);
			auxPrism->setRelativePosition(Vector3D(0.55,0.13,0.55));
			auxPrism->setRelativeOrientation(X_AXIS,PI/2);
			(*link)+=auxPrism;

			//CILINDRO SERVO PEQUE�O(Servo_Peq)
			auxCyl=new CylindricalPart(0.07,0.10);//Altura y radio
			auxCyl->setColor(0,0,0);
			auxCyl->setRelativePosition(Vector3D(0,0,0.56));
			(*link)+=auxCyl;

			//CILINDRO SERVO GRANDE(Servo_Gran)
			auxCyl=new CylindricalPart(0.03,0.175);//Altura y radio
			auxCyl->setColor(0,0,0);
			auxCyl->setRelativePosition(Vector3D(0,0,0.5));
			(*link)+=auxCyl;

			// A�ADIMOS AL VECTOR LINKS
			link->LinkTo(joints[1]);
			links.push_back(link);


//Joint[2]
////////////////////////////////////////////////////////////////////////////
//////////////////////////ARTICULACION 3 = LINK[3]//////////////////////////
////////////////////////////////////////////////////////////////////////////

			//JOINT[2] = ARTICULACION 3 ROTACIONAL 
			auxJoint=new SimpleJoint(25*PI/36 , -25*PI/36,true,0,Z_AXIS,false);
			auxJoint->setRelativePosition(Vector3D(1.1,0,0));//Desplazamiento a2
			auxJoint->setRelativeOrientation(0,0,0);
			auxJoint->LinkTo(joints[1]);
			auxJoint->setValue(q_init[2]);
			joints.push_back(auxJoint);
			//	joints[2]->setDrawReferenceSystem(true);
	actuator=new Actuator();
	actuator->linkTo(auxJoint);
	actuators.push_back(actuator);
	
			//NUEVO GRUPO DE PIEZAS
			link=new ComposedEntity;
			link->setName("Link 3");

//******************************************************************* //
// LA ARTICULACION 3 ESTA COMPUESTA POR 1 CILINDRO Y 6 PRISMAS IRREG. //
//******************************************************************* //

			// PRISMA IRREGULAR CENTRO ARRIBA(Pris_Cen_Ar)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.16,0));
			list.push_back(Vector2D(0.16,0));
			list.push_back(Vector2D(0.16,0.065));
			list.push_back(Vector2D(-0.16,0.065));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(255,0,0);
			auxPrism->setHeight(0.2);
			auxPrism->setRelativeOrientation(0,PI/2, -PI/2);
			auxPrism->setRelativePosition(Vector3D(0.56,0.1,0.22));
			(*link)+=auxPrism;

			//CILINDRO(Cilindro_Rojo)
			auxCyl=new CylindricalPart(0.03,0.175);//Altura y radio
			auxCyl->setColor(255,0,0);
			auxCyl->setRelativePosition(Vector3D(0,0,0.38));
			(*link)+=auxCyl;

			// PRISMA IRREGULAR DERECHA(Pris_Der)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.125,0));
			list.push_back(Vector2D(0.125,0));
			list.push_back(Vector2D(0.125,0.97));
			list.push_back(Vector2D(-0.125,0.97));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(255,0,0);
			auxPrism->setHeight(0.03);
			auxPrism->setRelativeOrientation(Z_AXIS,-PI/2);
			auxPrism->setRelativePosition(Vector3D(-0.01,0,0.38));
			(*link)+=auxPrism;

			// PRISMA IRREGULAR IZQUIERDA(Pris_Izq)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.155,0.18));
			list.push_back(Vector2D(0.155,-0.18));
			list.push_back(Vector2D(0.155,0.32));
			list.push_back(Vector2D(0.125,0.38));
			list.push_back(Vector2D(0.125,0.96));
			list.push_back(Vector2D(-0.125,0.96));
			list.push_back(Vector2D(-0.125,0.38));
			list.push_back(Vector2D(-0.155,0.32));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(255,0,0);
			auxPrism->setHeight(0.06);
			auxPrism->setRelativeOrientation(Z_AXIS,-PI/2);
			auxPrism->setRelativePosition(Vector3D(0,0,0));
			(*link)+=auxPrism;

			// PRISMA IRREGULAR CENTRO ABAJO(Pris_Cen_Ab)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.16,0));
			list.push_back(Vector2D(0.16,0));
			list.push_back(Vector2D(0.16,0.065));
			list.push_back(Vector2D(0.1,0.065));
			list.push_back(Vector2D(0.1,0.18));
			list.push_back(Vector2D(0.045,0.18));
			list.push_back(Vector2D(0.045,0.065));
			list.push_back(Vector2D(-0.045,0.065));
			list.push_back(Vector2D(-0.045,0.18));
			list.push_back(Vector2D(-0.1,0.18));
			list.push_back(Vector2D(-0.1,0.065));
			list.push_back(Vector2D(-0.16,0.065));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(255,0,0);
			auxPrism->setHeight(0.2);
			auxPrism->setRelativeOrientation(0,PI/2,-PI/2);
			
			auxPrism->setRelativePosition(Vector3D(0.38,0.1,0.22));
			(*link)+=auxPrism;

			// PRISMA IRREGULAR REFUERZO DERECHA(Pris_Ref_Der)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(0,0));
			list.push_back(Vector2D(0.04,0.045));
			list.push_back(Vector2D(0.04,0.81));
			list.push_back(Vector2D(0,0.81));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(255,0,0);
			auxPrism->setHeight(0.2);
			auxPrism->setRelativeOrientation(0,-PI/2,-PI/2);
	
			auxPrism->setRelativePosition(Vector3D(0.15,-0.13,0.41));
			(*link)+=auxPrism;

			// PRISMA IRREGULAR ARRIBA(Pris_Ar)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.16,0));
			list.push_back(Vector2D(-0.115,0));
			list.push_back(Vector2D(-0.115,0.05));
			list.push_back(Vector2D(0.115,0.05));
			list.push_back(Vector2D(0.155,0));
			list.push_back(Vector2D(0.16,0));
			list.push_back(Vector2D(0.16,0.11));
			list.push_back(Vector2D(-0.16,0.11));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(255,0,0);
			auxPrism->setHeight(0.25);
			auxPrism->setRelativeOrientation(-PI/2, -PI/2,0);
			
			auxPrism->setRelativePosition(Vector3D(0.85,-0.13,0.22));
			(*link)+=auxPrism;

			//CILINDRO SERVO GRANDE(Servo_Gran)
			auxCyl=new CylindricalPart(0.03,0.175);//Altura y radio
			auxCyl->setColor(0,0,0);
			auxCyl->setRelativePosition(Vector3D(0,0,-0.08));
			(*link)+=auxCyl;

			//CILINDRO SERVO PEQUE�O(Servo_Peq)
			auxCyl=new CylindricalPart(0.06,0.175);//Altura y radio
			auxCyl->setColor(0,0,0);
			auxCyl->setRelativePosition(Vector3D(0,0,-0.06));
			(*link)+=auxCyl;

			// SERVO4(Servo4)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.095,-0.2));
			list.push_back(Vector2D(0.095,-0.2));
			list.push_back(Vector2D(0.095,0.2));
			list.push_back(Vector2D(-0.095,0.2));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(0,0,0);
			auxPrism->setHeight(0.35);
			auxPrism->setRelativePosition(Vector3D(0.07,0,-0.01));
			auxPrism->setRelativeOrientation(Z_AXIS,-PI/2);
			(*link)+=auxPrism;

			// SERVO5(Servo5)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.055,-0.11));
			list.push_back(Vector2D(0.055,-0.11));
			list.push_back(Vector2D(0.055,0.11));
			list.push_back(Vector2D(-0.055,0.11));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(0,0,0);
			auxPrism->setHeight(0.25);
			auxPrism->setRelativePosition(Vector3D(0.67,0,0.23));
			auxPrism->setRelativeOrientation(Y_AXIS,PI/2);
			(*link)+=auxPrism;

			//CILINDRO REFUERZO SERVO(Cil_Ref)
			auxCyl=new CylindricalPart(0.06,0.08);//Altura y radio
			auxCyl->setColor(0,0,0);
			auxCyl->setRelativePosition(Vector3D(0.9,-0.15,0.22));
			auxCyl->setRelativeOrientation(Y_AXIS,PI/2);
			(*link)+=auxCyl;

			// A�ADIMOS AL VECTOR LINKS
			link->LinkTo(joints[2]);
			links.push_back(link);



			
////////////////////////////////////////////////////////////////////////////
//////////////////////////ARTICULACION 4 = LINK[4]//////////////////////////
////////////////////////////////////////////////////////////////////////////

			//JOINT[3] = ARTICULACION 4 ROTACIONAL 
			auxJoint=new SimpleJoint(7*PI/9 , -7*PI/9,true,0,Z_AXIS,0);
			auxJoint->setRelativePosition(Vector3D(1.0,0.0,0.2));
			auxJoint->setRelativeOrientation(Y_AXIS,PI/2);
			auxJoint->LinkTo(joints[2]);
			auxJoint->setValue(q_init[3]);
			joints.push_back(auxJoint);
			//	joints[3]->setDrawReferenceSystem(true);
	actuator=new Actuator();
	actuator->linkTo(auxJoint);
	actuators.push_back(actuator);
			//NUEVO GRUPO DE PIEZAS
			link=new ComposedEntity;
			link->setName("Link 4");

			//******************************************************************** //
			// LA ARTICULACION 4 ESTA COMPUESTA POR 2 CILINDROS Y 2 PRISMAS IRREG. //
			//******************************************************************** //

			// PRISMA IRREGULAR(Prisma)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.125,0));
			list.push_back(Vector2D(0.2,0));
			list.push_back(Vector2D(0.26,0.03));
			list.push_back(Vector2D(0.29,0.09));
			list.push_back(Vector2D(0.29,0.23));
			list.push_back(Vector2D(0.26,0.275));
			list.push_back(Vector2D(0.23,0.275));
			list.push_back(Vector2D(0.23,0.11));
			list.push_back(Vector2D(0.2,0.11));
			list.push_back(Vector2D(0.2,0.06));
			list.push_back(Vector2D(0.09,0.06));
			list.push_back(Vector2D(0.09,0.03));
			list.push_back(Vector2D(-0.09,0.03));
			list.push_back(Vector2D(-0.09,0.06));
			list.push_back(Vector2D(-0.125,0.06));
			list.push_back(Vector2D(-0.125,0.11));
			list.push_back(Vector2D(-0.155,0.11));
			list.push_back(Vector2D(-0.155,0.13));
			list.push_back(Vector2D(-0.185,0.13));
			list.push_back(Vector2D(-0.21,0.09));
			list.push_back(Vector2D(-0.185,0.03));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(255,233,0);
			auxPrism->setHeight(0.25);
			auxPrism->setRelativeOrientation(PI/2, 0 , -PI);
			
			auxPrism->setRelativePosition(Vector3D(0,-0.1,0));
			(*link)+=auxPrism;

			// PRISMA IRREGULAR IZQUIERDA(Pris_Izq)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.045,0));
			list.push_back(Vector2D(0.045,0));
			list.push_back(Vector2D(0.045,0.125));
			list.push_back(Vector2D(-0.045,0.125));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(255,233,0);
			auxPrism->setHeight(0.03);
			auxPrism->setRelativeOrientation(Y_AXIS,PI/2);
			auxPrism->setRelativePosition(Vector3D(0.16,-0.04,0.16));
			(*link)+=auxPrism;

			//CILINDRO IZQUIERDA(Cil_Izq)
			auxCyl=new CylindricalPart(0.03,0.065);
			auxCyl->setColor(255,233,0);
			auxCyl->setRelativePosition(Vector3D(0.16,0.2,0.2));
			auxCyl->setRelativeOrientation(0,PI/2,0);
			(*link)+=auxCyl;

			//CILINDRO DERECHA(Cil_Der)
			auxCyl=new CylindricalPart(0.03,0.175);
			auxCyl->setColor(255,233,0);
			auxCyl->setRelativePosition(Vector3D(-0.26,0.02,0.27));
			auxCyl->setRelativeOrientation(0,PI/2,0);
			(*link)+=auxCyl;


			//CILINDRO SERVO ARRIBA(Servo_Ar)
			auxCyl=new CylindricalPart(0.09,0.05);//Altura y radio
			auxCyl->setColor(0,0,0);
			auxCyl->setRelativePosition(Vector3D(-0.25,0.02,0.27));
			auxCyl->setRelativeOrientation(Y_AXIS,PI/2);
			(*link)+=auxCyl;

			//CILINDRO SERVO ABAJO(Servo_Ab)
			auxCyl=new CylindricalPart(0.05,0.05);//Altura y radio
			auxCyl->setColor(0,0,0);
			auxCyl->setRelativePosition(Vector3D(0,0,-0.04));
			(*link)+=auxCyl;

			// SERVO6(Servo6)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.055,-0.11));
			list.push_back(Vector2D(0.055,-0.11));
			list.push_back(Vector2D(0.055,0.11));
			list.push_back(Vector2D(-0.055,0.11));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(0,0,0);
			auxPrism->setHeight(0.25);
			auxPrism->setRelativePosition(Vector3D(-0.24,0.03,0.22));
			auxPrism->setRelativeOrientation(-PI/2,0,PI/2);
			
			(*link)+=auxPrism;

			// A�ADIMOS AL VECTOR LINKS
			link->LinkTo(joints[3]);
			links.push_back(link);





////////////////////////////////////////////////////////////////////////////
//////////////////////////ARTICULACION 5 = LINK[5]//////////////////////////
////////////////////////////////////////////////////////////////////////////

			//JOINT[4] = ARTICULACION 5 ROTACIONAL 
			auxJoint=new SimpleJoint(5*PI/9,-5*PI/9,true,0,Z_AXIS,false);
			auxJoint->setRelativePosition(Vector3D(-0.2,0,0.3));
			auxJoint->setRelativeOrientation(0,PI/2,0);
			auxJoint->LinkTo(joints[3]);
			auxJoint->setValue(q_init[4]);
			joints.push_back(auxJoint);
			//	joints[4]->setDrawReferenceSystem(true);
	actuator=new Actuator();
	actuator->linkTo(auxJoint);
	actuators.push_back(actuator);
			//NUEVO GRUPO DE PIEZAS
			link=new ComposedEntity;
			link->setName("Link 5");

			//******************************************************************* //
			// LA ARTICULACION 5 ESTA COMPUESTA POR 3 CILINDROS Y 1 PRISMA IRREG. //
			//******************************************************************* //

			// PRISMA IRREGULAR(Prisma)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.17,0));
			list.push_back(Vector2D(0.17,0));
			list.push_back(Vector2D(0.21,0.02));
			list.push_back(Vector2D(0.23,0.06));
			list.push_back(Vector2D(0.23,0.1));
			list.push_back(Vector2D(0.19,0.19));
			list.push_back(Vector2D(0.17,0.19));
			list.push_back(Vector2D(0.17,0.1));
			list.push_back(Vector2D(0.14,0.1));
			list.push_back(Vector2D(0.14,0.06));
			list.push_back(Vector2D(-0.14,0.06));
			list.push_back(Vector2D(-0.14,0.1));
			list.push_back(Vector2D(-0.17,0.1));
			list.push_back(Vector2D(-0.07,0.19));
			list.push_back(Vector2D(-0.19,0.19));
			list.push_back(Vector2D(-0.23,0.1));
			list.push_back(Vector2D(-0.23,0.06));
			list.push_back(Vector2D(-0.21,0.02));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(255,0,0);
			auxPrism->setHeight(0.25);
			auxPrism->setRelativeOrientation(PI/2, -PI/2, 0);
			
			auxPrism->setRelativePosition(Vector3D(-0.19,-0.12,0.19));
			(*link)+=auxPrism;

			// CILINDRO DERECHA(Cil_Der)
			auxCyl=new CylindricalPart(0.02,0.12);
			auxCyl->setColor(233,0,0);
			(*link)+=auxCyl;

			//CILINDRO IZQUIERDA(Cil_Izq)
			auxCyl=new CylindricalPart(0.02,0.12);
			auxCyl->setColor(233,0,0);
			auxCyl->setRelativePosition(Vector3D(0,0,0.36));
			(*link)+=auxCyl;


			//CILINDRO REFUERZO(Cil_Ref)
			auxCyl=new CylindricalPart(0.06,0.08);
			auxCyl->setColor(233,0,0);
			auxCyl->setRelativePosition(Vector3D(-0.13,0.15,0.20));
			auxCyl->setRelativeOrientation(Y_AXIS,-PI/2);
			(*link)+=auxCyl;

			// SERVO7(Servo7)
			auxPrism=new PrismaticPart;
			list.push_back(Vector2D(-0.055,-0.11));
			list.push_back(Vector2D(0.055,-0.11));
			list.push_back(Vector2D(0.055,0.11));
			list.push_back(Vector2D(-0.055,0.11));
			auxPrism->setPolygonalBase(list);
			list.clear();
			auxPrism->setColor(0,0,0);
			auxPrism->setHeight(0.25);
			auxPrism->setRelativePosition(Vector3D(-0.15,0.05,0.2));
			auxPrism->setRelativeOrientation(Y_AXIS,-PI/2);
			(*link)+=auxPrism;

			// A�ADIMOS AL VECTOR LINKS
			link->LinkTo(joints[4]);
			links.push_back(link);


			


////////////////////////////////////////////////////////////////////////////
//////////////////////////ARTICULACION 6 = LINK[6]//////////////////////////
////////////////////////////////////////////////////////////////////////////

			//JOINT[5] = ARTICULACION 6 ROTACIONAL 
			auxJoint=new SimpleJoint(PI,-PI,true,0,Z_AXIS,false);
			auxJoint->setRelativePosition(Vector3D(0,0,0));
			auxJoint->LinkTo(joints[4]);
			auxJoint->setValue(q_init[5]);
			joints.push_back(auxJoint);
			//	joints[5]->setDrawReferenceSystem(true);
	actuator=new Actuator();
	actuator->linkTo(auxJoint);
	actuators.push_back(actuator);
			//NUEVO GRUPO DE PIEZAS
			link=new ComposedEntity;
			link->setName("Link 6");

			//************************************************* //
			// LA ARTICULACION 6 ESTA COMPUESTA POR UN CILINDRO //
			//************************************************* //
			// CILINDRO:
			auxCyl=new CylindricalPart(0.06,0.03);//Altura y radio
			auxCyl->setColor(0,0,0);
			auxCyl->setRelativePosition(Vector3D(0,0,0));
			(*link)+=auxCyl;

			// A�ADIMOS AL VECTOR LINKS
			auxCyl->LinkTo(joints[5]);
			links.push_back(auxCyl);



			//Tcp
			tcp=new Tcp();
			tcp->setName("Tcp");
			tcp->setRelativePosition(Vector3D(0,0,0.06));
			tcp->LinkTo(joints[5]);
			tcp->setDrawReferenceSystem(true);

			//getConfigurationOf(q_init,conf);

			actuators[0]->setSimulationParameters(PI/12);//	15�/seg
			actuators[1]->setSimulationParameters(23*PI/36);//	115�/seg
			actuators[2]->setSimulationParameters(23*PI/36);//	115�/seg
			actuators[3]->setSimulationParameters(14*PI/9);//	280�/seg
			actuators[4]->setSimulationParameters(5*PI/3);//	300�/seg
			actuators[5]->setSimulationParameters(5*PI/3);//	300�/seg


			(*this)+=links[0];
}

bool EUITIbotSim::getCoordinatesOf(vector<double> &_q)
{
	double v;
	_q.clear();
	for(int i=0;i<6;i++)
	{
		getJointValue(i,v);
		_q.push_back(v);
	}
	return true;
}

bool EUITIbotSim::inverseKinematics(Transformation3D t06, vector<double> &_q, unsigned char _conf)
{
	if(_conf == 0x00)
		_conf=getCurrentConfiguration();

	return EUITIbotInverseKinematics(t06,_q,_conf);
}

bool EUITIbotSim::EUITIbotInverseKinematics(Transformation3D t06, vector<double> &_q, unsigned char _conf)
{
//*****************************************
	vector<double> q_act;
	unsigned char c_act;
	getCoordinatesOf(q_act);//Save current coordiantes
	getConfigurationOf(q_act,c_act);
//*****************************************

	double d1=0.66;
	double d2=0.15;
	double d4=0.432;
	double d6=0.065;
	double a2=0.432;
	double a3=-0.02;//�?

	if(_conf == 0x00)
		_conf=getCurrentConfiguration();

	double _s, _e, _w;
	configuration(_conf,_s,_e,_w);

/*	if(_conf != c_act)//Si cambia de configuracion, retorna
		return false;
	*/

	Vector3D pm = t06.position - t06.getVectorW()*(d6);

	double z_prima = pm.z - d1;

	double ee = sqrt(pm.x*pm.x + pm.y*pm.y - (d2)*(d2));

	double dd = sqrt((a3)*(a3) + (a2)*(a2));

	double alfa = atan(abs(a3)/a2);

//THETA 2
	double c2a = (ee*ee + z_prima*z_prima - (a2)*(a2) - dd*dd)/(2*(a2)*dd);
	if((1 - c2a*c2a) < 0)
		return false;
	//double theta2 = PI/2 - atan2((_e*sqrt(1 - c2a*c2a)),(c2a)) + alfa;
	double theta2 =  - atan2((_e*sqrt(1 - c2a*c2a)),(c2a)) + alfa;

//THETA 1
	double beta = atan2(z_prima,ee);
	double phi = atan2(dd*sqrt(1 - c2a*c2a),((d4)+dd*c2a));
	double theta1 = -beta + _e*phi + PI/2;

//THETA 0
	double a11=atan2(pm.y,pm.x);
	double a22=atan2(ee,d2);
	double theta0 = a11 - _s*a22;
	if(pm.x < 0 && pm.y > 0 && q_act[0] < -PI/2)
		theta0-=2*PI;

//DESACOPLO CINEMATICO
	OrientationMatrix m06,m03,m36;

	Matrix3x3 &aux03=m03;

	m06=t06.orientation;

//Definicion de T03

/***
Se definen previamente las operaciones de senos y cosenos para que no se repita
la misma operacion varias veces ya que estas operaciones requieren mucho computo.
***/


//Meto las 3 primeras coordenadas finales y corregidas
	setJointValue(0,theta0);
	setJointValue(1,theta1);
	setJointValue(2,theta2);

//Obtengo la informacion que necesito
	Transformation3D auxm = joints[3]->getAbsoluteT3D();

	//Devuelvo la posicion previa
	for(int i=0;i<6;i++)
		setJointValue(i,q_act[i]);

//aux03 tiene la misma direcicon de memoria que m03
	aux03=auxm.orientation;
	
	m36=(m03.inverted())*m06;

//THETA 3
	double theta3 = atan2(m36[1][2] , m36[0][2]) + PI/2;
//THETA 4
	double theta4 = acos(m36[2][2]);
//THETA 5
	double theta5 = atan2(m36[2][1] , -m36[2][0]);

//CONFIGURACIONES

	_q.push_back(theta0);
	_q.push_back(theta1);
	_q.push_back(theta2);
	_q.push_back(theta3);
	_q.push_back(theta4);
	_q.push_back(theta5);

/*	if(!checkJointValues(_q))
		return false;
*/

	for(int i=0;i<6;i++){if(fabs(_q[i])<EPS){_q[i]=0;}}

	return true;
}

bool EUITIbotSim::getConfigurationOf(const vector<double> &_q, unsigned char &_conf)
{
//Compruebo tama�o y rangos de coordenadas
	if(!checkJointValues(_q))return false;

	double _s,_e,_w;

//HOMBRO
	if(_q[1]>0)//Hombro izquierdo
		_s=-1.0;
	else//Hombro derecho
		_s=1.0;

//CODO
	double d1=0.02*cos(_q[1] + _q[2]);
	double d2=0.432*sin(_q[1] + _q[2]);
	double d3=0.432*sin(_q[1]);

	if(0 < (d2-d1-d3))
		_e=-1.0;
	else
		_e=1.0;

//WRIST
	vector<double> q_aux;
	getCoordinatesOf(q_aux);
	for(int i=0;i<6;i++)
		joints[i]->setValue(_q[i]);
	Vector3D v1=joints[3]->getAbsoluteT3D().getVectorW();
	Vector3D v2=tcp->getAbsoluteT3D().getVectorW();
	for(int i=0;i<6;i++)
		joints[i]->setValue(q_aux[i]);

	if(_q[3] != 0)
	{
		if(sin(_q[4])*sin(_q[3] + PI/2) > 0)
			_w=-1.0;
		else
			_w=1.0;//WRIST DOWN
	}
	else
	{
		if(sin(_q[4]) > 0)
			_w=-1.0;
		else
			_w=1.0;//WRIST DOWN
	}

	return configuration(_s,_e,_w,_conf);
}



bool EUITIbotSim::configuration(unsigned char _conf, double& _s, double& _e, double& _w)
{
	_s=_e=_w=-1.0;
	if(_conf == INIT_EUITI_BOT)return true;
	if(_conf & SHOULDERRIGHT)_s=1.0;
	if(_conf & ELBOWDOWN)_e=1.0;
	if(_conf & WRISTDOWN)_w=1.0;
	return true;
}

bool EUITIbotSim::configuration(double _s, double _e, double _w, unsigned char &_conf)
{
	_conf = INIT_EUITI_BOT;
	if( _s == 1.0)_conf = (_conf|SHOULDERRIGHT);
	if( _e == 1.0)_conf = (_conf|ELBOWDOWN);
	if( _w == 1.0)_conf = (_conf|WRISTDOWN);
	return true;
}




void EUITIbotSim::simulate(double delta_t)
{

	RobotSim::simulate(delta_t);

}

};//Namespace mr
